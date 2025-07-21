#include <SDL3/SDL.h>
#include "engine/engine.h"
#include "game/game.h"
#include "game/scenes/entities/test_entities.h"
#include <cglm/cglm.h>
#include <unistd.h>

#define SLIME_STANDING_NAME "still"
#define SLIME_SPRINT_NAME "sprint"
Entity SetupTestEntity(Imzi_Engine_Ptr engine)
{
    Game *game = (Game *)engine->game_data;

    Entity entity = {0};

    int32_t still_animation_index = Imzi_AssetManager2DCreateAnimationFromPath(engine, game->manager, "assets/slime.png", SLIME_STANDING_NAME, &(SDL_FRect){0, 0, 64, 64}, 64, 64, 1, 1, false);
    Imzi_AssetManager2DCreateAnimationFromPath(engine, game->manager, "assets/sprint_slime_sprint.png", SLIME_SPRINT_NAME, &(SDL_FRect){0, 0, 64, 64}, 64, 64, 5, 0.1, true);

    TestEntityData *data = SDL_malloc(sizeof(TestEntityData));

    data->animation_player = Imzi_CreateAnimationPlayer(game->manager, still_animation_index);
    data->map = Imzi_CreateTileMap();

    int32_t grass_index = Imzi_AssetManager2DCreateSpriteFromPath(engine, game->manager, "assets/tilemap.png", "grass", &(SDL_FRect){96, 0, 64, 64});

    for (int32_t width = 0; width < engine->ctx->width; width += 64)
    {
        Imzi_CreateTileInTileMap(data->map, grass_index, (vec2){width, engine->ctx->height - 64});
    }

    glm_vec2_zero(data->position);
    glm_vec2_zero(data->velocity);

    data->position[0] = 10;
    data->position[1] = engine->ctx->height - 128;

    entity.data = data;
    entity.renderPtr = RenderTestEntity;
    entity.updatePtr = UpdateTestEntity;

    return entity;
}

void RenderTestEntity(Imzi_Engine_Ptr engine, void *data, double frame_time)
{
    TestEntityData *entity_data = (TestEntityData *)data;
    SDL_SetRenderDrawColor(engine->ctx->renderer, 255, 0, 0, 255);
    Imzi_UpdateAnimationPlayer(&entity_data->animation_player, frame_time);
    Imzi_RenderTileMap(engine, entity_data->animation_player.manager, entity_data->map);
    Imzi_AnimationPlayerRender(engine, &entity_data->animation_player, entity_data->position);
    SDL_RenderDebugTextFormat(engine->ctx->renderer, 10,10, "FPS: %lf", 1 / frame_time);
}

#define PIXEL_PER_METER 100.0 * 2

void UpdateTestEntity(Imzi_Engine_Ptr engine, void *data, double frame_time)
{
    (void)engine;
    TestEntityData *entity_data = (TestEntityData *)data;

    const bool *state = SDL_GetKeyboardState(NULL);

    entity_data->animation_player.animation_index = Imzi_AssetManager2DGetAnimationByName(entity_data->animation_player.manager, SLIME_SPRINT_NAME);

    if (state[SDL_SCANCODE_D])
    {
        // if (index != 0 && index != 6)
        // {
        Imzi_StartAnimationPlayerByName(&entity_data->animation_player, SLIME_SPRINT_NAME);
        entity_data->position[0] += PIXEL_PER_METER * frame_time;
        entity_data->animation_player.h_flip = false;
        // }
    }
    else if (state[SDL_SCANCODE_A])
    {
        // if (index != 0 && index != 6)
        // {
        Imzi_StartAnimationPlayerByName(&entity_data->animation_player, SLIME_SPRINT_NAME);
        entity_data->position[0] -= PIXEL_PER_METER * frame_time;
        entity_data->animation_player.h_flip = true;
    }
    else
    {
        Imzi_StartAnimationPlayerByName(&entity_data->animation_player, SLIME_STANDING_NAME);
    }
}
