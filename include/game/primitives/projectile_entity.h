#ifndef PROJECTILE_ENTITY_H
#define PROJECTILE_ENTITY_H

#include "cglm/types.h"
#include "engine/entity.h"
#include <stdint.h>
typedef struct {
  vec2 velocity;
  vec2 position;
  uint32_t sprite_index;
  double lifetime;
  double elapsed_time;

} ProjectileEntity;

void SetupProjectileEntity(uint32_t sprite_index, int32_t lifetime,
                           vec2 velocity, vec2 position, Entity *entity);

#endif // PROJECTILE_ENTITY_H
