#ifndef ENGINE_H
#define ENGINE_H

#include "engine/renderer.h"
#include <SDL3/SDL.h>
#include <stdint.h>

typedef struct {
  Imzi_Renderer renderer;
  void *game_data;
  uint64_t new_time;
  uint64_t old_time;
} Imzi_Engine;

typedef Imzi_Engine *Imzi_Engine_Ptr;

void Imzi_InitEngine(const char *title, int width, int height,
                     Imzi_Engine_Ptr engine);

void Imzi_DeinitEngine(Imzi_Engine_Ptr engine);

#endif
