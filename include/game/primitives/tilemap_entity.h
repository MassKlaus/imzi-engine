#ifndef TILEMAP_ENTITY_H
#define TILEMAP_ENTITY_H

#include "engine/entity.h"
#include "engine/visuals/tilemap.h"

typedef struct TileMapEntity {
  TileMap *tilemap;
} TileMapEntity;

void SetupTileMapEntity(TileMap *tilemap, Entity *entity);

#endif // !TILEMAP_ENTITY_H
