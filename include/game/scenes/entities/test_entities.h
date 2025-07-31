#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include "engine/entity.h"
#include "engine/players/animation_player.h"
#include <SDL3_image/SDL_image.h>
#include <cglm/cglm.h>
#include <stdint.h>

typedef struct {
  AnimationPlayer animation_player;
  int32_t background;
  vec2 position;
  vec2 velocity;
  vec2 acceleration;
} TestEntityData;

Entity SetupTestEntity(Imzi_Engine_Ptr engine);

#endif
