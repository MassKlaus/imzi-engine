#ifndef GAME_H
#define GAME_H

#include "cglm/types.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/scene.h"

typedef struct {
  AssetManager2D *manager;
  Scene *active_scene;
  // Place camera here
  vec2 camera;
} Game;

#endif
