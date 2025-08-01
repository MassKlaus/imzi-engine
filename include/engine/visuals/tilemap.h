#ifndef TILEMAP_H
#define TILEMAP_H

#include "engine/renderer.h"
#include <cglm/cglm.h>

#define MAX_TILE_COUNT 100

typedef struct {
  int32_t sprite_index;
  vec2 position;
} Tile;

typedef struct {
  Tile tiles[MAX_TILE_COUNT];
  int32_t tile_count;
} TileMap;

TileMap *Imzi_SetupTileMap();

int32_t Imzi_SetupTileInTileMap(TileMap *map, int32_t sprite_index,
                                vec2 position);

int32_t Imzi_SetupTileInTileMapFromPath(Imzi_Renderer_Ptr renderer,
                                        TileMap *map, const char *path,
                                        const char *name, SDL_FRect *area,
                                        vec2 position);

int32_t Imzi_SetupTileInTileMapFromName(Imzi_Renderer_Ptr renderer,
                                        TileMap *map, const char *name,
                                        vec2 position);

void Imzi_TileMapRender(Imzi_Renderer_Ptr renderer, TileMap *map);

#endif
