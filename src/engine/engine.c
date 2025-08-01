#include "engine/engine.h"
#include "core/imzi.h"

void Imzi_InitEngine(const char *title, int width, int height,
                     Imzi_Engine_Ptr engine) {
  Imzi_Init(&engine->ctx, title, width, height);
  engine->new_time = 0;
  engine->old_time = 0;
  engine->zoom = 1.0;
}

void Imzi_DeinitEngine(Imzi_Engine_Ptr engine) { Imzi_Deinit(&engine->ctx); }
