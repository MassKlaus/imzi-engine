#include "engine/engine.h"
#include "engine/scene.h"
#include "game/scenes/test_scene.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "game/game.h"

Scene* active_scene; 

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    Imzi_Engine_Ptr engine = Imzi_InitEngine("Imzi Window.", 1280, 720);
    *appstate = engine;
    Game *game = SDL_malloc(sizeof(Game));
    game->manager = Imzi_CreateAssetManager2D();

    SDL_SetRenderVSync(engine->ctx->renderer, 1);
    engine->game_data = game;

    active_scene = SetupTest1Scene(engine);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    Imzi_Engine_Ptr ctx = (Imzi_Engine_Ptr)appstate;
    (void)ctx;

    if (event->type == SDL_EVENT_QUIT || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE))
    {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}


SDL_AppResult SDL_AppIterate(void *appstate)
{

    Imzi_Engine_Ptr engine = (Imzi_Engine_Ptr)appstate;
    engine->old_time = engine->new_time;
    engine->new_time = SDL_GetTicksNS();

    double frame_time = (engine->new_time - engine->old_time) / (1000000000.0);

    if (Imzi_ShouldClose(engine->ctx))
    {
        return SDL_APP_SUCCESS;
    }

    SDL_SetRenderDrawColor(engine->ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->ctx->renderer); /* code */

    if (active_scene)
    {
        Imzi_UpdateScene(engine, active_scene, frame_time);
        Imzi_RenderScene(engine, active_scene, frame_time);
    }

    SDL_RenderPresent(engine->ctx->renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    Imzi_Engine_Ptr engine = (Imzi_Engine_Ptr)appstate;
    Imzi_Deinit(engine->ctx);

    if (result == SDL_APP_FAILURE)
    {
        SDL_Log("FAILED BAD");
    }
    
}