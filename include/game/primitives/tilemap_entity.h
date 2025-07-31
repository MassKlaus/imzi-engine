#ifndef TILEMAP_ENTITY_H
#define TILEMAP_ENTITY_H

#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/visuals/tilemap.h"

typedef struct TileMapEntity {
  TileMap *tilemap;
} TileMapEntity;

Entity SetupTileMapEntity(TileMap *tilemap);

#endif // !TILEMAP_ENTITY_H
