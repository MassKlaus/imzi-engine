const std = @import("std");

// Although this function looks imperative, note that its job is to
// declaratively construct a build graph that will be executed by an external
// runner.

const targets: []const std.Target.Query = &.{
    .{ .cpu_arch = .aarch64, .os_tag = .macos },
    .{ .cpu_arch = .x86_64, .os_tag = .linux },
    .{ .cpu_arch = .x86_64, .os_tag = .windows },
};

pub fn build(b: *std.Build) !void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard optimization options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall. Here we do not
    // set a preferred release mode, allowing the user to decide how to optimize.
    const optimize = b.standardOptimizeOption(.{});

    // This creates a "module", which represents a collection of source files alongside
    // some compilation options, such as optimization mode and linked system libraries.

    // We will also create a module for our other entry point, 'main.zig'.

    const main = b.addModule("imzi-engine", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true, // Link the C standard library
    });

    // add all c files in the src directory to directory
    var src_dir = try std.fs.cwd().openDir("src", .{
        .access_sub_paths = true,
        .iterate = true,
    });
    defer src_dir.close();

    var dir_walker = try src_dir.walk(b.allocator);
    defer dir_walker.deinit();

    var c_files = std.ArrayListUnmanaged([:0]const u8){};
    defer c_files.deinit(b.allocator);

    while (try dir_walker.next()) |entry| {
        if (entry.kind != .file) continue;

        // Only add C files to the build.iI
        if (std.ascii.eqlIgnoreCase(std.fs.path.extension(entry.path), ".c")) {
            // Add the C file to the executable module.
            const path = try b.allocator.dupeZ(u8, entry.path);

            try c_files.append(b.allocator, path);
        }
    }

    main.addCSourceFiles(.{
        .root = b.path("src"),
        .files = c_files.items,
        .flags = &[_][]const u8{ "-std=gnu11", "-Wall", "-Wextra", "-Werror", 
            // Sanitizers
            "-fsanitize=address,undefined,leak",
            "-fno-omit-frame-pointer",
            "-fno-optimize-sibling-calls",
        },
    });

    main.sanitize_c = true;

    main.linkSystemLibrary("asan", .{});      // AddressSanitizer
    main.linkSystemLibrary("ubsan", .{});

    main.addIncludePath(b.path("include"));
    main.addIncludePath(b.path("vendors/SDL3/include"));
    main.addIncludePath(b.path("vendors/SDL3_image/include"));
    main.addIncludePath(b.path("vendors/cglm/include"));

    main.addLibraryPath(b.path("vendors/SDL3/lib"));
    main.addLibraryPath(b.path("vendors/SDL3_image/lib"));

    main.addCMacro("SDL_MAIN_USE_CALLBACKS", "1");

    main.linkSystemLibrary("SDL3", .{ .preferred_link_mode = .static, .needed = true });
    main.linkSystemLibrary("SDL3_image", .{ .preferred_link_mode = .dynamic, .needed = true });

    // This creates another `std.Build.Step.Compile`, but this one builds an executable
    // rather than a static library.
    const exe = b.addExecutable(.{
        .name = "imzi_engine",
        .root_module = main,
    });


    if (target.result.os.tag == .windows) {
        b.install_path = "./zig-out/windows/";
        b.dest_dir = "./zig-out/windows/";
        b.exe_dir = "./zig-out/windows/";

        b.installBinFile("./vendors/SDL3/lib/SDL3.dll", "./SDL3.dll");
        b.installBinFile("./vendors/SDL3_image/lib/SDL3_image.dll", "./SDL3_image.dll");
    } else if (target.result.os.tag == .linux) {
        b.install_path = "./zig-out/linux/";
        b.dest_dir = "./zig-out/linux/";
        b.exe_dir = "./zig-out/linux/";

        b.installBinFile("./vendors/SDL3/lib/libSDL3.so.0.3.0", "./libSDL3.so.0.3.0");
        b.installBinFile("./vendors/SDL3_image/lib/libSDL3_image.so.0.3.0", "./libSDL3_image.so.0.3.0");
    }

    b.installDirectory(.{ .source_dir = b.path("./assets/"), .install_dir = .{ .custom = "./" }, .install_subdir = "assets" });
    // This declares intent for the executable to be installed into the
    // standard location when the user invokes the "install" step (the default
    // step when running `zig build`).
    // b.addInstallArtifact(exe, .{ .dest_dir = b.dest_dir });
    b.installArtifact(exe);

    // This *creates* a Run step in the build graph, to be executed when another
    // step is evaluated that depends on it. The next line below will establish
    // such a dependency.
    const run_cmd = b.addRunArtifact(exe);

    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    // This is not necessary, however, if the application depends on other installed
    // files, this ensures they will be present and in the expected location.
    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
