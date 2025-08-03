#include "SDL3/SDL_init.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_video.h"
#include "engine/engine.h"
#include "engine/scene.h"
#include "game/game.h"
#include "game/scenes/test_scene.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  Game *game = SDL_malloc(sizeof(Game));
  SDL_zero(*game);
  Imzi_Engine_Ptr engine = SDL_malloc(sizeof(Imzi_Engine));
  SDL_zero(*engine);
  Imzi_InitEngine("Imzi Window.", 1280, 720, engine);
  engine->game_data = game;
  *appstate = engine;

  // SDL_GL_SetRenderVSync(engine->renderer.ctx.renderContext, 1);
  SetupTest1Scene(engine, &game->active_scene);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  Imzi_Engine_Ptr ctx = (Imzi_Engine_Ptr)appstate;
  (void)ctx;

  if (event->type == SDL_EVENT_QUIT ||
      (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE)) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  Imzi_Engine_Ptr engine = (Imzi_Engine_Ptr)appstate;
  Game *game = (Game *)engine->game_data;
  engine->old_time = engine->new_time;
  engine->new_time = SDL_GetTicksNS();

  double frame_time = (engine->new_time - engine->old_time) / (1000000000.0);

  if (Imzi_ShouldClose(&engine->renderer.ctx)) {
    return SDL_APP_SUCCESS;
  }

  glClear(GL_COLOR_BUFFER_BIT);

  Imzi_UpdateScene(engine, &game->active_scene, frame_time);
  Imzi_RenderScene(engine, &game->active_scene, frame_time);

  // SDL_RenderPresent(engine->renderer.ctx.renderContext);
  SDL_GL_SwapWindow(engine->renderer.ctx.window);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  Imzi_Engine_Ptr engine = (Imzi_Engine_Ptr)appstate;
  Game *game = (Game *)engine->game_data;

  SDL_free(game);
  Imzi_DeinitEngine(engine);

  if (result == SDL_APP_FAILURE) {
    SDL_Log("FAILED BAD");
  }
}
