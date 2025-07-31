#include <engine/engine.h>
#include <string.h>

Imzi_Engine_Ptr Imzi_InitEngine(const char *title, int width, int height) {
  Imzi_Context_Ptr ctx = Imzi_Init(title, width, height);
  Imzi_Engine_Ptr engine = SDL_malloc(sizeof(Imzi_Engine));
  memset(engine, 0, sizeof(Imzi_Engine));

  engine->ctx = ctx;
  engine->new_time = 0;
  engine->old_time = 0;
  engine->zoom = 1.0;

  return engine;
}
