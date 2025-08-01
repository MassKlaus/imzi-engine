#ifndef GAME_H
#define GAME_H

#include "cglm/types.h"
#include "engine/scene.h"

typedef struct {
  Scene active_scene;
  // Place camera here
  vec2 camera;
} Game;

#endif
