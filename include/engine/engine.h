#ifndef ENGINE_H
#define ENGINE_H

#include "cglm/types.h"
#include "core/imzi.h"
#include <SDL3/SDL.h>
#include <stdint.h>

typedef struct {
  Imzi_Context_Ptr ctx;
  void *game_data;
  uint64_t new_time;
  uint64_t old_time;
  vec2 render_offset;
  float zoom;
} Imzi_Engine;

typedef Imzi_Engine *Imzi_Engine_Ptr;

Imzi_Engine_Ptr Imzi_InitEngine(const char *title, int width, int height);

#endif
