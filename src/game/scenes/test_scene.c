#include "game/scenes/test_scene.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/scene.h"
#include "engine/visuals/tilemap.h"
#include "game/game.h"
#include "game/primitives/background_entity.h"
#include "game/primitives/tilemap_entity.h"
#include "game/scenes/entities/test_entities.h"
#include <SDL3/SDL.h>

Scene *SetupTest1Scene(Imzi_Engine_Ptr engine) {
  Scene *scene = SDL_malloc(sizeof(Scene));
  SDL_memset(scene, 0, sizeof(Scene));
  Game *game = (Game *)engine->game_data;

  Entity entity = SetupTestEntity(engine);

  int32_t background = Imzi_AssetManager2DCreateSpriteFromPath(
      engine, game->manager, "assets/temp.png", "background", NULL);

  int32_t grass_index = Imzi_AssetManager2DCreateSpriteFromPath(
      engine, game->manager, "assets/tilemap.png", "grass",
      &(SDL_FRect){128, 64, 64, 64});

  Entity background_entity = SetupBackgroundEntity(background);
  TileMap *tilemap = Imzi_SetupTileMap();

  for (int32_t width = 0; width < engine->ctx->width; width += 64) {
    Imzi_SetupTileInTileMap(tilemap, grass_index,
                            (vec2){width, engine->ctx->height - 64});
  }

  Entity tilemap_entity = SetupTileMapEntity(tilemap);

  Imzi_AddEntityToScene(scene, background_entity);
  Imzi_AddEntityToScene(scene, tilemap_entity);
  Imzi_AddEntityToScene(scene, entity);

  return scene;
}
