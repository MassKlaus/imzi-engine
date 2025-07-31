#ifndef SCENE_H
#define SCENE_H

#include "engine/engine.h"
#include "engine/entity.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_SCENE_ENTITIES 100000

typedef struct {
  Entity entities[MAX_SCENE_ENTITIES];
  int32_t entity_count;
} Scene;

Scene *SetupScene();
bool Imzi_AddEntityToScene(Scene *scene, Entity entity);
bool Imzi_RemoveEntityFromScene(Scene *scene, uint32_t entity_id);
bool Imzi_RemoveMarkedEntitiesFromScene(Scene *scene);

void Imzi_RenderScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time);
void Imzi_UpdateScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time);

#endif
