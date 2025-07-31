#!/usr/bin/env python3

import json
import os
import glob

def generate_compile_commands():
    # Get current working directory (project root)
    project_root = os.path.abspath(".")
    
    # Find all C files in src directory
    c_files = []
    for root, dirs, files in os.walk("src"):
        for file in files:
            if file.endswith(".c"):
                rel_path = os.path.relpath(os.path.join(root, file), ".")
                c_files.append(rel_path)
    
    # Generate compile commands
    compile_commands = []
    
    for c_file in c_files:
        command = [
            "clang",
            "-xc",
            "-std=gnu11",
            "-Wall",
            "-Wextra",
            "-Werror",
            "-Iinclude",
            "-Ivendors/SDL3/include", 
            "-Ivendors/SDL3_image/include",
            "-Ivendors/cglm/include",
            "-DSDL_MAIN_USE_CALLBACKS=1",
            "-c",
            c_file
        ]
        
        compile_commands.append({
            "directory": project_root,
            "file": os.path.join(project_root, c_file),
            "command": " ".join(command)
        })
    
    # Write to compile_commands.json
    with open("compile_commands.json", "w") as f:
        json.dump(compile_commands, f, indent=2)
    
    print(f"Generated compile_commands.json with {len(compile_commands)} entries")
    for cmd in compile_commands:
        print(f"  - {cmd['file']}")

if __name__ == "__main__":
    generate_compile_commands()
