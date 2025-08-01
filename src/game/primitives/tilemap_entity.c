#include "game/primitives/tilemap_entity.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/entity.h"
#include "engine/visuals/tilemap.h"
#include <assert.h>
#include <stdbool.h>

void RenderTileMapEntity(Imzi_Engine_Ptr engine, Entity *entity,
                         double frame_time) {
  (void)frame_time;
  TileMapEntity *entity_data = (TileMapEntity *)entity->data;

  assert(entity_data->tilemap != NULL);
  Imzi_RenderTileMap(&engine->ctx, &engine->manager, entity_data->tilemap);
}

void UpdateTileMapEntity(Imzi_Engine_Ptr engine, Entity *entity,
                         double frame_time) {
  (void)frame_time;
  (void)entity;
  (void)engine;
}

void SetupTileMapEntity(TileMap *tilemap, Entity *entity) {
  TileMapEntity *tile_map_entity = SDL_malloc(sizeof(TileMapEntity));
  SDL_memset(entity, 0, sizeof(TileMapEntity));

  tile_map_entity->tilemap = tilemap;

  entity->data = tile_map_entity;
  entity->renderPtr = RenderTileMapEntity;
  entity->updatePtr = UpdateTileMapEntity;
  entity->render_layer = 0;
}
