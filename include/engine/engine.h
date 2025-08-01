#ifndef ENGINE_H
#define ENGINE_H

#include "cglm/types.h"
#include "core/imzi.h"
#include "engine/managers/asset_manager_2d.h"
#include <SDL3/SDL.h>
#include <stdint.h>

typedef struct {
  Imzi_Context ctx;
  AssetManager2D manager;
  void *game_data;
  uint64_t new_time;
  uint64_t old_time;
  vec2 render_offset;
  float zoom;
} Imzi_Engine;

typedef Imzi_Engine *Imzi_Engine_Ptr;

void Imzi_InitEngine(const char *title, int width, int height,
                     Imzi_Engine_Ptr engine);

#endif
