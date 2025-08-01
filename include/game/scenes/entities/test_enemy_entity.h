#ifndef TEST_ENEMY_ENTITY
#define TEST_ENEMY_ENTITY

#include "engine/entity.h"
#include "engine/players/animation_player.h"
#include <stdint.h>

typedef struct {
  AnimationPlayer animation_player;
  int32_t background;
  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  uint32_t target;
} TestEnemyEntityData;

void SetupTestEnemyEntity(Imzi_Engine_Ptr engine, Entity *entity,
                          uint32_t target);

#endif // !TEST_ENEMY
