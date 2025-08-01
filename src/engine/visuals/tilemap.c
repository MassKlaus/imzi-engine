#include "engine/visuals/tilemap.h"
#include "engine/renderer.h"
#include "engine/visuals/sprite_sheet.h"
#include <assert.h>

TileMap *Imzi_SetupTileMap() {
  TileMap *map = SDL_malloc(sizeof(TileMap));

  map->tile_count = 0;
  return map;
}

int32_t Imzi_SetupTileInTileMap(TileMap *map, int32_t sprite_index,
                                vec2 position) {
  if (map->tile_count == MAX_TILE_COUNT) {
    return -1;
  }

  Tile tile = {0};

  glm_vec2_copy(position, tile.position);
  tile.sprite_index = sprite_index;

  map->tiles[map->tile_count++] = tile;

  return map->tile_count - 1;
}

int32_t Imzi_SetupTileInTileMapFromPath(Imzi_Renderer_Ptr renderer,
                                        TileMap *map, const char *path,
                                        const char *name, SDL_FRect *area,
                                        vec2 position) {
  int32_t sprite_index =
      Imzi_RendererCreateSpriteFromPath(renderer, path, name, area);

  if (sprite_index == -1) {
    return -1;
  }

  return Imzi_SetupTileInTileMap(map, sprite_index, position);
}

int32_t Imzi_SetupTileInTileMapFromName(Imzi_Renderer_Ptr renderer,
                                        TileMap *map, const char *name,
                                        vec2 position) {
  int32_t sprite_index = Imzi_RendererGetSpriteByName(renderer, name);

  if (sprite_index == -1) {
    return -1;
  }

  return Imzi_SetupTileInTileMap(map, sprite_index, position);
}

void Imzi_TileMapRender(Imzi_Renderer_Ptr renderer, TileMap *map) {
  Imzi_RendererDrawSprite(renderer, 1, (vec2){0, 0});
  for (int32_t i = 0; i < map->tile_count; i++) {
    Tile tile = map->tiles[i];
    Imzi_RendererDrawSprite(renderer, tile.sprite_index, tile.position);
  }
}
