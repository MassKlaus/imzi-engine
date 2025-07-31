#include "game/scenes/entities/test_entities.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_stdinc.h"
#include "cglm/types.h"
#include "cglm/vec2.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/managers/asset_manager_2d.h"
#include "game/game.h"
#include "game/primitives/projectile_entity.h"
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define SLIME_STANDING_NAME "still"
#define SLIME_SPRINT_NAME "sprint"
#define SLIME_PROJECTILE_NAME "slime_projectile"

void RenderTestEntity(Imzi_Engine_Ptr engine, Entity *entity,
                      double frame_time) {
  TestEntityData *entity_data = (TestEntityData *)entity->data;
  SDL_SetRenderDrawColor(engine->ctx->renderer, 255, 0, 0, 255);
  Imzi_UpdateAnimationPlayer(&entity_data->animation_player, frame_time);
  Imzi_AnimationPlayerRender(engine, &entity_data->animation_player,
                             entity_data->position);
  SDL_RenderDebugTextFormat(engine->ctx->renderer, 10, 10, "FPS: %lf",
                            1 / frame_time);
}

#define PIXELS_PER_METER 100.0
#define GRAVITY PIXELS_PER_METER * 9.8
#define SPEED PIXELS_PER_METER * 4
#define JUMP_IMPULSE PIXELS_PER_METER * 8

bool grounded = true;
bool jumping = false;
void UpdateTestEntity(Imzi_Engine_Ptr engine, Entity *entity,
                      double frame_time) {
  Game *game = (Game *)engine->game_data;
  TestEntityData *entity_data = (TestEntityData *)entity->data;

  const bool *state = SDL_GetKeyboardState(NULL);

  entity_data->animation_player.animation_index =
      Imzi_AssetManager2DGetAnimationByName(
          entity_data->animation_player.manager, SLIME_SPRINT_NAME);

  entity_data->acceleration[1] = GRAVITY;

  if (state[SDL_SCANCODE_SPACE] && grounded) {
    entity_data->velocity[1] = -JUMP_IMPULSE;
    grounded = false;
    jumping = true;
  }

  if (!state[SDL_SCANCODE_SPACE] && !grounded) {
    entity_data->acceleration[1] += GRAVITY;
    jumping = false;
  }

  if (state[SDL_SCANCODE_D]) {
    // if (index != 0 && index != 6)
    // {
    Imzi_StartAnimationPlayerByName(&entity_data->animation_player,
                                    SLIME_SPRINT_NAME);
    entity_data->velocity[0] = SPEED;
    entity_data->animation_player.h_flip = false;
    // }
  } else if (state[SDL_SCANCODE_A]) {
    // if (index != 0 && index != 6)
    // {
    Imzi_StartAnimationPlayerByName(&entity_data->animation_player,
                                    SLIME_SPRINT_NAME);
    entity_data->velocity[0] = -SPEED;
    entity_data->animation_player.h_flip = true;
  } else {
    Imzi_StartAnimationPlayerByName(&entity_data->animation_player,
                                    SLIME_STANDING_NAME);
    entity_data->velocity[0] = 0;
  }

  if (state[SDL_SCANCODE_RIGHT]) {
    // if (index != 0 && index != 6)
    // {
    engine->render_offset[0] -= SPEED * frame_time;
  } else if (state[SDL_SCANCODE_LEFT]) {
    // if (index != 0 && index != 6)
    // {
    engine->render_offset[0] += SPEED * frame_time;
  }

  if (state[SDL_SCANCODE_UP]) {
    // if (index != 0 && index != 6)
    // {
    engine->render_offset[1] += SPEED * frame_time;
  } else if (state[SDL_SCANCODE_DOWN]) {
    // if (index != 0 && index != 6)
    // {
    engine->render_offset[1] -= SPEED * frame_time;
  }

  entity_data->velocity[0] += entity_data->acceleration[0] * frame_time;
  entity_data->velocity[1] += entity_data->acceleration[1] * frame_time;

  entity_data->position[0] += entity_data->velocity[0] * frame_time;
  entity_data->position[1] += entity_data->velocity[1] * frame_time;

  if (entity_data->position[1] > engine->ctx->height - 128) {
    entity_data->position[1] = engine->ctx->height - 128;
    entity_data->acceleration[1] = 0;
    entity_data->velocity[1] = 0;
    grounded = true;
  }

  vec2 slime_center;
  slime_center[0] = entity_data->position[0] + 32;
  slime_center[1] = entity_data->position[1] + 32;

  float vertical_lag_range = 64;
  float camera_target =
      (engine->render_offset[0] + (engine->ctx->width / 2.0) - slime_center[0]);

  if (camera_target > vertical_lag_range ||
      camera_target < -vertical_lag_range) {

    camera_target =
        SDL_clamp(camera_target, -vertical_lag_range, vertical_lag_range);

    engine->render_offset[0] =
        SDL_ceil(slime_center[0] - (engine->ctx->width / 2.0) + camera_target);
    engine->render_offset[1] =
        SDL_ceil(slime_center[1] - (engine->ctx->height / 2.0));
  }
  if (state[SDL_SCANCODE_E]) {

    uint32_t projectile_sprite_index = Imzi_AssetManager2DGetSpriteByName(
        game->manager, SLIME_PROJECTILE_NAME);

    float direction = entity_data->animation_player.h_flip ? -1 : 1;
    vec2 position;
    glm_vec2_copy(entity_data->position, position);
    position[1] += 32;

    Entity projectile = SetupProjectileEntity(
        projectile_sprite_index, 2.0,
        (vec2){direction * PIXELS_PER_METER * 10, 0}, position);

    Imzi_AddEntityToScene(game->active_scene, projectile);
  }
}

Entity SetupTestEntity(Imzi_Engine_Ptr engine) {
  Game *game = (Game *)engine->game_data;

  int32_t still_animation_index = Imzi_AssetManager2DCreateAnimationFromPath(
      engine, game->manager, "assets/slime.png", SLIME_STANDING_NAME,
      &(SDL_FRect){0, 0, 64, 64}, 64, 64, 1, 1, false);
  Imzi_AssetManager2DCreateAnimationFromPath(
      engine, game->manager, "assets/sprint_slime_sprint.png",
      SLIME_SPRINT_NAME, &(SDL_FRect){0, 0, 64, 64}, 64, 64, 5, 0.1, true);

  Imzi_AssetManager2DCreateSpriteFromPath(
      engine, game->manager, "assets/prejectile.png", SLIME_PROJECTILE_NAME,
      &(SDL_FRect){0, 0, 32, 32});

  TestEntityData *data = SDL_malloc(sizeof(TestEntityData));
  SDL_memset(data, 0, sizeof(TestEntityData));

  data->animation_player =
      Imzi_SetupAnimationPlayer(game->manager, still_animation_index);

  glm_vec2_zero(data->position);
  glm_vec2_zero(data->velocity);

  data->position[0] = 10;
  data->position[1] = engine->ctx->height - 128;

  Entity entity = {0};
  entity.data = data;
  entity.render_layer = 1;
  entity.renderPtr = RenderTestEntity;
  entity.updatePtr = UpdateTestEntity;

  return entity;
}
