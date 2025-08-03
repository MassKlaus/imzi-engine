#include "game/scenes/entities/player_entity.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_stdinc.h"
#include "cglm/types.h"
#include "engine/engine.h"
#include "engine/entity.h"
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

void RenderPlayerEntity(Imzi_Engine_Ptr engine, Entity *entity,
                        double frame_time) {
  PlayerEntityData *entity_data = (PlayerEntityData *)entity->data;
  Imzi_UpdateAnimationPlayer(&entity_data->animation_player, frame_time);
  Imzi_AnimationPlayerRender(&engine->renderer, &entity_data->animation_player,
                             entity_data->position);
}

#define PIXELS_PER_METER 100.0
#define GRAVITY PIXELS_PER_METER * 9.8
#define SPEED PIXELS_PER_METER * 4
#define JUMP_IMPULSE PIXELS_PER_METER * 8

static bool grounded = true;
static bool jumping = false;
void UpdatePlayerEntity(Imzi_Engine_Ptr engine, Entity *entity,
                        double frame_time) {
  PlayerEntityData *entity_data = (PlayerEntityData *)entity->data;

  const bool *state = SDL_GetKeyboardState(NULL);

  entity_data->animation_player.animation_index =
      Imzi_RendererGetAnimationByName(&engine->renderer, SLIME_SPRINT_NAME);

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
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_SPRINT_NAME);
    entity_data->velocity[0] = SPEED;
    entity_data->animation_player.h_flip = false;
    // }
  } else if (state[SDL_SCANCODE_A]) {
    // if (index != 0 && index != 6)
    // {
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_SPRINT_NAME);
    entity_data->velocity[0] = -SPEED;
    entity_data->animation_player.h_flip = true;
  } else {
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_STANDING_NAME);
    entity_data->velocity[0] = 0;
  }

  if (state[SDL_SCANCODE_RIGHT]) {
    // if (index != 0 && index != 6)
    // {
    engine->renderer.render_shift[0] += SPEED * frame_time;
  } else if (state[SDL_SCANCODE_LEFT]) {
    // if (index != 0 && index != 6)
    // {
    engine->renderer.render_shift[0] -= SPEED * frame_time;
  }

  if (state[SDL_SCANCODE_UP]) {
    // if (index != 0 && index != 6)
    // {
    engine->renderer.render_shift[1] -= SPEED * frame_time;
  } else if (state[SDL_SCANCODE_DOWN]) {
    // if (index != 0 && index != 6)
    // {
    engine->renderer.render_shift[1] += SPEED * frame_time;
  }

  entity_data->velocity[0] += entity_data->acceleration[0] * frame_time;
  entity_data->velocity[1] += entity_data->acceleration[1] * frame_time;

  entity_data->position[0] += entity_data->velocity[0] * frame_time;
  entity_data->position[1] += entity_data->velocity[1] * frame_time;

  if (entity_data->position[1] > engine->renderer.ctx.height - 128) {
    entity_data->position[1] = engine->renderer.ctx.height - 128;
    entity_data->acceleration[1] = 0;
    entity_data->velocity[1] = 0;
    grounded = true;
  }

  vec2 slime_center;
  slime_center[0] = entity_data->position[0] + 32;
  slime_center[1] = entity_data->position[1] + 32;

  float horizontal_lag_range = 64;

  // Target camera position (where camera should be to center the slime)
  float step = slime_center[0] - (engine->renderer.render_shift[0] +
                                  (engine->renderer.ctx.width / 2.0));

  // Only move if outside lag range
  if (step > horizontal_lag_range) {
    // Slime is too far right, move camera right
    engine->renderer.render_shift[0] += step - horizontal_lag_range;
  } else if (step < -horizontal_lag_range) {
    // Slime is too far left, move camera left
    engine->renderer.render_shift[0] += step + horizontal_lag_range;
  }

  if (state[SDL_SCANCODE_E]) {
    uint32_t projectile_sprite_index =
        Imzi_RendererGetSpriteByName(&engine->renderer, SLIME_PROJECTILE_NAME);

    float direction = entity_data->animation_player.h_flip ? -1 : 1;
    vec2 position;
    glm_vec2_copy(entity_data->position, position);
    position[1] += 32;

    Game *game = (Game *)engine->game_data;
    Entity *projectile_entity = Imzi_AddEntityToScene(&game->active_scene);
    SetupProjectileEntity(projectile_sprite_index, 2.0,
                          (vec2){direction * PIXELS_PER_METER * 10, 0},
                          position, projectile_entity);
  }
}

void SetupPlayerEntity(Imzi_Engine_Ptr engine, Entity *entity) {
  int32_t still_animation_index = Imzi_RendererCreateAnimationFromPath(
      &engine->renderer, "assets/slime.png", SLIME_STANDING_NAME,
      &(SDL_FRect){0, 0, 64, 64}, 64, 64, 1, 1, false);

  Imzi_RendererCreateAnimationFromPath(
      &engine->renderer, "assets/sprint_slime_sprint.png", SLIME_SPRINT_NAME,
      &(SDL_FRect){0, 0, 64, 64}, 64, 64, 5, 0.1, true);

  Imzi_RendererCreateSpriteFromPath(&engine->renderer, "assets/prejectile.png",
                                    SLIME_PROJECTILE_NAME,
                                    &(SDL_FRect){0, 0, 32, 32});

  PlayerEntityData *data = SDL_malloc(sizeof(PlayerEntityData));
  SDL_memset(data, 0, sizeof(PlayerEntityData));

  data->animation_player = Imzi_SetupAnimationPlayer(still_animation_index);

  glm_vec2_zero(data->position);
  glm_vec2_zero(data->velocity);

  data->position[0] = 10;
  data->position[1] = 0;

  entity->data = data;
  entity->render_layer = 1;
  entity->renderPtr = RenderPlayerEntity;
  entity->updatePtr = UpdatePlayerEntity;
}
