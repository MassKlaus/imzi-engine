#ifndef ENTITIY_H
#define ENTITIY_H

#include "engine/engine.h"
#include <SDL3/SDL.h>
#include <inttypes.h>

typedef struct Entity Entity;

typedef struct Entity {
  void *data;
  void (*updatePtr)(Imzi_Engine_Ptr engine, Entity *data, double frame_time);
  void (*renderPtr)(Imzi_Engine_Ptr engine, Entity *data, double frame_time);
  int32_t render_layer;
  uint32_t id;
} Entity;

#endif
