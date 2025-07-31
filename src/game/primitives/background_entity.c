#include "game/primitives/background_entity.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/entity.h"
#include "engine/managers/asset_manager_2d.h"
#include "game/game.h"
#include <stdint.h>

void RenderBackgroundEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)frame_time;
  BackgroundEntity *entity_data = (BackgroundEntity *)entity->data;
  Game *game = (Game *)engine->game_data;
  Imzi_RenderSpriteToStatic(
      engine, game->manager, entity_data->sprite_index,
      &(SDL_FRect){0.0, 0.0, engine->ctx->width, engine->ctx->height});
}

void UpdateBackgroundEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)frame_time;
  (void)entity;
  (void)engine;
}

Entity SetupBackgroundEntity(int32_t sprite_index) {
  BackgroundEntity *entity = SDL_malloc(sizeof(BackgroundEntity));
  SDL_memset(entity, 0, sizeof(BackgroundEntity));
  entity->sprite_index = sprite_index;

  return (Entity){entity, RenderBackgroundEntity, RenderBackgroundEntity, -1, 0,
                  false};
}
