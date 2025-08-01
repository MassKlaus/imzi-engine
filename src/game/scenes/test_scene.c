#include "game/scenes/test_scene.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/scene.h"
#include "engine/visuals/tilemap.h"
#include "game/primitives/background_entity.h"
#include "game/primitives/tilemap_entity.h"
#include "game/scenes/entities/player_entity.h"
#include "game/scenes/entities/test_enemy_entity.h"
#include <SDL3/SDL.h>

void SetupTest1Scene(Imzi_Engine_Ptr engine, Scene *scene) {
  Entity *player_entity = Imzi_AddEntityToScene(scene);
  SetupPlayerEntity(engine, player_entity);

  Entity *enemy_entity = Imzi_AddEntityToScene(scene);
  SetupTestEnemyEntity(engine, enemy_entity, player_entity->id);

  int32_t background = Imzi_RendererCreateSpriteFromPath(
      &engine->renderer, "assets/temp.png", "background", NULL);

  Entity *background_entity = Imzi_AddEntityToScene(scene);
  SetupBackgroundEntity(background, background_entity);

  TileMap *tilemap = Imzi_SetupTileMap();

  int32_t grass_index =
      Imzi_RendererCreateSpriteFromPath(&engine->renderer, "assets/tilemap.png",
                                        "grass", &(SDL_FRect){128, 64, 64, 64});

  for (int32_t width = 0; width < engine->renderer.ctx.width; width += 64) {
    Imzi_SetupTileInTileMap(tilemap, grass_index,
                            (vec2){width, engine->renderer.ctx.height - 64});
  }

  Entity *tilemap_entity = Imzi_AddEntityToScene(scene);
  SetupTileMapEntity(tilemap, tilemap_entity);
}
