#include "game/primitives/projectile_entity.h"
#include "SDL3/SDL_stdinc.h"
#include "cglm/vec2.h"
#include "engine/entity.h"
#include "engine/managers/asset_manager_2d.h"
#include "game/game.h"
#include <stdbool.h>
#include <stdlib.h>

void UpdateProjectileEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)engine;
  ProjectileEntity *data = (ProjectileEntity *)entity->data;

  data->elapsed_time += frame_time;

  if (data->elapsed_time >= data->lifetime) {
    // NOTE: Current implementation assures us that this would be deleted after
    // all entities have been processed sucessfully
    entity->marked_for_delete = true;
  }

  data->position[0] += data->velocity[0] * frame_time;
  data->position[1] += data->velocity[1] * frame_time;
}

void RenderProjectileEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)frame_time;
  Game *game = (Game *)engine->game_data;
  ProjectileEntity *data = (ProjectileEntity *)entity->data;
  Imzi_RenderSprite(engine, game->manager, data->sprite_index, data->position);
}

Entity SetupProjectileEntity(uint32_t sprite_index, int32_t lifetime,
                             vec2 velocity, vec2 position) {
  ProjectileEntity *data = malloc(sizeof(ProjectileEntity));
  SDL_memset(data, 0, sizeof(ProjectileEntity));

  data->lifetime = lifetime;
  data->sprite_index = sprite_index;
  glm_vec2_copy(velocity, data->velocity);
  glm_vec2_copy(position, data->position);

  return (Entity){data, UpdateProjectileEntity, RenderProjectileEntity, 2, 0,
                  false};
}
