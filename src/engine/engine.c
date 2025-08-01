#include "engine/engine.h"
#include "engine/renderer.h"

void Imzi_InitEngine(const char *title, int width, int height,
                     Imzi_Engine_Ptr engine) {
  Imzi_InitRenderer(title, width, height, &engine->renderer);
  engine->new_time = 0;
  engine->old_time = 0;
}

void Imzi_DeinitEngine(Imzi_Engine_Ptr engine) {
  Imzi_DeinitRenderer(&engine->renderer);
}
