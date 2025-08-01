run
+- run imzi_engine
   +- zig build-exe imzi_engine Debug native 58 errors
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:23:34: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_SetRenderDrawColor(engine->ctx.renderer, 255, 0, 0, 255);
                         ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:25:39: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_AnimationPlayerRender(&engine->ctx, &engine->manager,
                              ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:25:53: error: no member named 'manager' in 'Imzi_Engine'
  Imzi_AnimationPlayerRender(&engine->ctx, &engine->manager,
                                            ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:28:37: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_RenderDebugTextFormat(engine->ctx.renderer, 10, 10, "FPS: %lf",
                            ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:46:54: error: no member named 'manager' in 'Imzi_Engine'
      Imzi_AssetManager2DGetAnimationByName(&engine->manager,
                                             ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:66:18: error: no member named 'manager' in 'Imzi_Engine'
        &engine->manager, &entity_data->animation_player, SLIME_SPRINT_NAME);
         ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:74:18: error: no member named 'manager' in 'Imzi_Engine'
        &engine->manager, &entity_data->animation_player, SLIME_SPRINT_NAME);
         ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:79:18: error: no member named 'manager' in 'Imzi_Engine'
        &engine->manager, &entity_data->animation_player, SLIME_STANDING_NAME);
         ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:86:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[0] -= SPEED * frame_time;
    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:90:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[0] += SPEED * frame_time;
    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:96:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[1] += SPEED * frame_time;
    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:100:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[1] -= SPEED * frame_time;
    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:109:42: error: no member named 'ctx' in 'Imzi_Engine'
  if (entity_data->position[1] > engine->ctx.height - 128) {
                                 ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:110:40: error: no member named 'ctx' in 'Imzi_Engine'
    entity_data->position[1] = engine->ctx.height - 128;
                               ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:122:16: error: no member named 'render_offset' in 'Imzi_Engine'
      (engine->render_offset[0] + (engine->ctx.width / 2.0) - slime_center[0]);
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:122:44: error: no member named 'ctx' in 'Imzi_Engine'
      (engine->render_offset[0] + (engine->ctx.width / 2.0) - slime_center[0]);
                                   ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:130:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[0] =
    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:131:45: error: no member named 'ctx' in 'Imzi_Engine'
        SDL_ceil(slime_center[0] - (engine->ctx.width / 2.0) + camera_target);
                                    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c:132:13: error: no member named 'render_offset' in 'Imzi_Engine'
    engine->render_offset[1] =
    ~~~~~~~~^
:1:1: error: too many errors emitted, stopping now
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:20:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/temp.png", "background", NULL);
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:20:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/temp.png", "background", NULL);
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:28:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/tilemap.png", "grass",
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:28:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/tilemap.png", "grass",
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:31:43: error: no member named 'ctx' in 'Imzi_Engine'
  for (int32_t width = 0; width < engine->ctx.width; width += 64) {
                                  ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c:33:51: error: no member named 'ctx' in 'Imzi_Engine'
                            (vec2){width, engine->ctx.height - 64});
                                          ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:24:34: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_SetRenderDrawColor(engine->ctx.renderer, 255, 0, 0, 255);
                         ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:26:39: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_AnimationPlayerRender(&engine->ctx, &engine->manager,
                              ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:26:53: error: no member named 'manager' in 'Imzi_Engine'
  Imzi_AnimationPlayerRender(&engine->ctx, &engine->manager,
                                            ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:29:37: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_RenderDebugTextFormat(engine->ctx.renderer, 10, 10, "FPS: %lf",
                            ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:64:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/slime.png", SLIME_STANDING_NAME,
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:64:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/slime.png", SLIME_STANDING_NAME,
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:67:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/sprint_slime_sprint.png",
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:67:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/sprint_slime_sprint.png",
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:71:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/prejectile.png",
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:71:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, "assets/prejectile.png",
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c:83:31: error: no member named 'ctx' in 'Imzi_Engine'
  data->position[1] = engine->ctx.height - 128;
                      ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/engine/visuals/tilemap.c:55:5: error: call to undeclared function 'Imzi_RenderSprite'; ISO C99 and later do not support implicit function declarations
    Imzi_RenderSprite(ctx, manager, tile.sprite_index, tile.position);
    ^
/home/massine/Coding/imzi-engine/src/engine/players/animation_player.c:60:35: error: incompatible pointer types passing 'Imzi_Context_Ptr' (aka 'struct Imzi_Context *') to parameter of type 'Imzi_Renderer_Ptr' (aka 'Imzi_Renderer *')
  Imzi_RenderPartialSpriteSheetEx(ctx, sheet, &src, &dest, flip);
                                  ^
/home/massine/Coding/imzi-engine/include/engine/renderer.h:33:56: note: passing argument to parameter 'renderer' here
void Imzi_RenderPartialSpriteSheetEx(Imzi_Renderer_Ptr renderer,
                                                       ^
/home/massine/Coding/imzi-engine/src/engine/players/animation_player.c:60:40: error: incompatible pointer to integer conversion passing 'SpriteSheet *' to parameter of type 'int32_t' (aka 'int')
  Imzi_RenderPartialSpriteSheetEx(ctx, sheet, &src, &dest, flip);
                                       ^
/home/massine/Coding/imzi-engine/include/engine/renderer.h:34:46: note: passing argument to parameter 'sprite_sheet' here
                                     int32_t sprite_sheet, SDL_FRect *src,
                                             ^
/home/massine/Coding/imzi-engine/src/engine/engine.c:13:32: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_DeinitRenderer(&engine->ctx);
                       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/main.c:21:30: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_SetRenderVSync(engine->ctx.renderer, 1);
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/main.c:47:33: error: no member named 'ctx' in 'Imzi_Engine'
  if (Imzi_ShouldClose(&engine->ctx)) {
                        ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/main.c:51:27: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_RenderClear(engine->ctx.renderer); /* code */
                  ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/main.c:56:29: error: no member named 'ctx' in 'Imzi_Engine'
  SDL_RenderPresent(engine->ctx.renderer);
                    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/main.c:63:24: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_Deinit(&engine->ctx);
               ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c:11:3: error: call to undeclared function 'Imzi_RenderSpriteToStatic'; ISO C99 and later do not support implicit function declarations
  Imzi_RenderSpriteToStatic(
  ^
/home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c:12:16: error: no member named 'ctx' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, entity_data->sprite_index,
       ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c:12:30: error: no member named 'manager' in 'Imzi_Engine'
      &engine->ctx, &engine->manager, entity_data->sprite_index,
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c:13:38: error: no member named 'ctx' in 'Imzi_Engine'
      &(SDL_FRect){0.0, 0.0, engine->ctx.width, engine->ctx.height});
                             ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c:13:57: error: no member named 'ctx' in 'Imzi_Engine'
      &(SDL_FRect){0.0, 0.0, engine->ctx.width, engine->ctx.height});
                                                ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/tilemap_entity.c:14:31: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_RenderTileMap(&engine->ctx, &engine->manager, entity_data->tilemap);
                      ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/tilemap_entity.c:14:45: error: no member named 'manager' in 'Imzi_Engine'
  Imzi_RenderTileMap(&engine->ctx, &engine->manager, entity_data->tilemap);
                                    ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/engine/renderer.c:37:6: error: conflicting types for 'Imzi_RenderPartialSpriteSheet'
void Imzi_RenderPartialSpriteSheet(Imzi_Renderer_Ptr renderer,
     ^
/home/massine/Coding/imzi-engine/include/engine/renderer.h:29:6: note: previous declaration is here
void Imzi_RenderPartialSpriteSheet(Imzi_Renderer_Ptr renderer,
     ^
/home/massine/Coding/imzi-engine/src/engine/renderer.c:44:6: error: conflicting types for 'Imzi_RenderPartialSpriteSheetEx'
void Imzi_RenderPartialSpriteSheetEx(Imzi_Renderer_Ptr renderer,
     ^
/home/massine/Coding/imzi-engine/include/engine/renderer.h:33:6: note: previous declaration is here
void Imzi_RenderPartialSpriteSheetEx(Imzi_Renderer_Ptr renderer,
     ^
/home/massine/Coding/imzi-engine/src/engine/renderer.c:48:51: error: comparison of integers of different signs: 'int32_t' (aka 'int') and 'uint32_t' (aka 'unsigned int')
  SDL_assert(renderer->manager.sprite_sheet_count > sprite_sheet_index);
             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~
/home/massine/Coding/imzi-engine/vendors/SDL3/include/SDL3/SDL_assert.h:482:53: note: expanded from macro 'SDL_assert'
#   define SDL_assert(condition) SDL_enabled_assert(condition)
                                                    ^
/home/massine/Coding/imzi-engine/vendors/SDL3/include/SDL3/SDL_assert.h:364:19: note: expanded from macro 'SDL_enabled_assert'
        while ( !(condition) ) { \
                  ^
/home/massine/Coding/imzi-engine/src/game/primitives/projectile_entity.c:30:30: error: no member named 'ctx' in 'Imzi_Engine'
  Imzi_RenderSprite(&engine->ctx, &engine->manager, data->sprite_index,
                     ~~~~~~~~^
/home/massine/Coding/imzi-engine/src/game/primitives/projectile_entity.c:30:44: error: no member named 'manager' in 'Imzi_Engine'
  Imzi_RenderSprite(&engine->ctx, &engine->manager, data->sprite_index,
                                   ~~~~~~~~^
error: the following command failed with 58 compilation errors:
/usr/bin/zig build-exe -cflags -std=gnu11 -Wall -Wextra -Werror -- /home/massine/Coding/imzi-engine/src/core/imzi.c /home/massine/Coding/imzi-engine/src/glad.c /home/massine/Coding/imzi-engine/src/main.c /home/massine/Coding/imzi-engine/src/game/scenes/test_scene.c /home/massine/Coding/imzi-engine/src/game/scenes/entities/test_enemy_entity.c /home/massine/Coding/imzi-engine/src/game/scenes/entities/player_entity.c /home/massine/Coding/imzi-engine/src/game/primitives/background_entity.c /home/massine/Coding/imzi-engine/src/game/primitives/projectile_entity.c /home/massine/Coding/imzi-engine/src/game/primitives/tilemap_entity.c /home/massine/Coding/imzi-engine/src/engine/renderer.c /home/massine/Coding/imzi-engine/src/engine/managers/asset_manager_2d.c /home/massine/Coding/imzi-engine/src/engine/scene.c /home/massine/Coding/imzi-engine/src/engine/visuals/sprite_sheet.c /home/massine/Coding/imzi-engine/src/engine/visuals/tilemap.c /home/massine/Coding/imzi-engine/src/engine/engine.c /home/massine/Coding/imzi-engine/src/engine/players/animation_player.c -search_paths_first_static -lSDL3 -search_paths_first -needed-lSDL3_image -ODebug -I /home/massine/Coding/imzi-engine/include -I /home/massine/Coding/imzi-engine/vendors/SDL3/include -I /home/massine/Coding/imzi-engine/vendors/SDL3_image/include -I /home/massine/Coding/imzi-engine/vendors/cglm/include -DSDL_MAIN_USE_CALLBACKS=1 -L /home/massine/Coding/imzi-engine/vendors/SDL3/lib -L /home/massine/Coding/imzi-engine/vendors/SDL3_image/lib -Mroot -lc --cache-dir /home/massine/Coding/imzi-engine/.zig-cache --global-cache-dir /home/massine/.cache/zig --name imzi_engine --zig-lib-dir /usr/lib/zig/ --listen=- 
Build Summary: 3/8 steps succeeded; 1 failed
run transitive failure
+- run imzi_engine transitive failure
   +- zig build-exe imzi_engine Debug native 58 errors
   +- install transitive failure
      +- install imzi_engine transitive failure
         +- zig build-exe imzi_engine Debug native (reused)
error: the following build command failed with exit code 1:
/home/massine/Coding/imzi-engine/.zig-cache/o/653e9d1fd5b3ba98522f3933594e0702/build /usr/bin/zig /usr/lib/zig /home/massine/Coding/imzi-engine /home/massine/Coding/imzi-engine/.zig-cache /home/massine/.cache/zig --seed 0xe719330f -Za33e9c4237651363 run
