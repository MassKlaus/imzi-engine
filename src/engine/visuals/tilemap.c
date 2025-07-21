#include "engine/visuals/tilemap.h"

TileMap *Imzi_CreateTileMap()
{
    TileMap *map = SDL_malloc(sizeof(TileMap));

    map->tile_count = 0;
    return map;
}

int32_t Imzi_CreateTileInTileMap(TileMap *map, int32_t sprite_index, vec2 position)
{
    if (map->tile_count == MAX_TILE_COUNT)
    {
        return -1;
    }

    Tile tile = {0};

    glm_vec2_copy(position, tile.position);
    tile.sprite_index = sprite_index;

    map->tiles[map->tile_count++] = tile;

    return map->tile_count - 1;
}

int32_t Imzi_CreateTileInTileMapFromPath(Imzi_Engine_Ptr engine, AssetManager2D *manager, TileMap *map, const char *path, const char *name, SDL_FRect *area, vec2 position)
{
    int32_t sprite_index = Imzi_AssetManager2DCreateSpriteFromPath(engine, manager, path, name, area);

    if (sprite_index == -1)
    {
        return -1;
    }

    return Imzi_CreateTileInTileMap(map, sprite_index, position);
}

int32_t Imzi_CreateTileInTileMapFromName(AssetManager2D *manager, TileMap *map, const char *name, vec2 position)
{
    int32_t sprite_index = Imzi_AssetManager2DGetSpriteByName(manager, name);

    if (sprite_index == -1)
    {
        return -1;
    }

    return Imzi_CreateTileInTileMap(map, sprite_index, position);
}


void Imzi_RenderTileMap(Imzi_Engine_Ptr engine, AssetManager2D *manager, TileMap *map)
{
    for (int32_t i = 0; i < map->tile_count; i++)
    {
        Tile tile = map->tiles[i];
        Imzi_RenderSprite(engine, manager, tile.sprite_index, tile.position);
    }
    
}