#include "game/scenes/entities/test_enemy_entity.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/players/animation_player.h"
#include "engine/renderer.h"
#include "engine/scene.h"
#include "game/game.h"
#include "game/scenes/entities/player_entity.h"
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define SLIME_STANDING_NAME "still"
#define SLIME_SPRINT_NAME "sprint"
#define SLIME_PROJECTILE_NAME "slime_projectile"

void RenderTestEnemyEntity(Imzi_Engine_Ptr engine, Entity *entity,
                           double frame_time) {
  TestEnemyEntityData *entity_data = (TestEnemyEntityData *)entity->data;
  Imzi_UpdateAnimationPlayer(&entity_data->animation_player, frame_time);
  Imzi_AnimationPlayerRender(&engine->renderer, &entity_data->animation_player,
                             entity_data->position);
}

#define PIXELS_PER_METER 100.0
#define GRAVITY PIXELS_PER_METER * 9.8
#define SPEED PIXELS_PER_METER
#define JUMP_IMPULSE PIXELS_PER_METER * 8

void UpdateTestEnemyEntity(Imzi_Engine_Ptr engine, Entity *entity,
                           double frame_time) {
  TestEnemyEntityData *entity_data = (TestEnemyEntityData *)entity->data;
  Game *game = (Game *)engine->game_data;

  Entity *player_entity =
      Imzi_FindEntityInScene(&game->active_scene, entity_data->target);

  if (player_entity == NULL) {
    SDL_Log("Krug not happy");
    return;
  }

  PlayerEntityData *player_entity_data =
      (PlayerEntityData *)player_entity->data;

  float direction =
      entity_data->position[0] > player_entity_data->position[0] ? -1 : 1;

  if (SDL_abs((int)(entity_data->position[0] -
                    player_entity_data->position[0])) < 20) {
    direction = 0;
  }

  entity_data->velocity[0] = direction * SPEED;
  entity_data->position[0] += entity_data->velocity[0] * frame_time;

  if (direction > 0) {
    // if (index != 0 && index != 6)
    // {
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_SPRINT_NAME);
    entity_data->animation_player.h_flip = false;
    // }
  } else if (direction < 0) {
    // if (index != 0 && index != 6)
    // {
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_SPRINT_NAME);
    entity_data->animation_player.h_flip = true;
  } else {
    Imzi_StartAnimationPlayerByName(
        &engine->renderer, &entity_data->animation_player, SLIME_STANDING_NAME);
    entity_data->velocity[0] = 0;
  }
}

void SetupTestEnemyEntity(Imzi_Engine_Ptr engine, Entity *entity,
                          uint32_t target_id) {
  int32_t still_animation_index = Imzi_RendererCreateAnimationFromPath(
      &engine->renderer, "assets/slime.png", SLIME_STANDING_NAME,
      &(SDL_FRect){0, 0, 64, 64}, 64, 64, 1, 1, false);
  Imzi_RendererCreateAnimationFromPath(
      &engine->renderer, "assets/sprint_slime_sprint.png", SLIME_SPRINT_NAME,
      &(SDL_FRect){0, 0, 64, 64}, 64, 64, 5, 0.1, true);

  Imzi_RendererCreateSpriteFromPath(&engine->renderer, "assets/prejectile.png",
                                    SLIME_PROJECTILE_NAME,
                                    &(SDL_FRect){0, 0, 32, 32});

  TestEnemyEntityData *data = SDL_malloc(sizeof(TestEnemyEntityData));
  SDL_memset(data, 0, sizeof(TestEnemyEntityData));

  data->animation_player = Imzi_SetupAnimationPlayer(still_animation_index);

  glm_vec2_zero(data->position);
  glm_vec2_zero(data->velocity);

  data->position[0] = 200;
  data->position[1] = engine->renderer.ctx.height - 128;

  data->target = target_id;

  entity->data = data;
  entity->render_layer = 1;
  entity->renderPtr = RenderTestEnemyEntity;
  entity->updatePtr = UpdateTestEnemyEntity;
}
