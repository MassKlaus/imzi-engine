#ifndef BACKGROUND_ENTITY_H
#define BACKGROUND_ENTITY_H

#include "engine/entity.h"
#include <stdint.h>

typedef struct BackgroundEntity {
  int32_t sprite_index;
} BackgroundEntity;

void SetupBackgroundEntity(int32_t sprite_index, Entity *entity);

#endif // !BACKGROUND_ENTITY_H
