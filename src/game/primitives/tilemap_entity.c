#include "game/primitives/tilemap_entity.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/entity.h"
#include "engine/visuals/tilemap.h"
#include "game/game.h"
#include <assert.h>
#include <stdbool.h>

void RenderTileMapEntity(Imzi_Engine_Ptr engine, Entity *entity,
                         double frame_time) {
  (void)frame_time;
  TileMapEntity *entity_data = (TileMapEntity *)entity->data;
  Game *game = (Game *)engine->game_data;
  assert(entity_data->tilemap != NULL);
  Imzi_RenderTileMap(engine, game->manager, entity_data->tilemap);
}

void UpdateTileMapEntity(Imzi_Engine_Ptr engine, Entity *entity,
                         double frame_time) {
  (void)frame_time;
  (void)entity;
  (void)engine;
}

Entity SetupTileMapEntity(TileMap *tilemap) {
  TileMapEntity *entity = SDL_malloc(sizeof(TileMapEntity));
  SDL_memset(entity, 0, sizeof(TileMapEntity));

  entity->tilemap = tilemap;

  return (Entity){entity, RenderTileMapEntity, RenderTileMapEntity, 0, 0,
                  false};
}
