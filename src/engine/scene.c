
#include "engine/scene.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int compare_render_layer(const void *a, const void *b) {
  const Entity *entity_a = (const Entity *)a;
  const Entity *entity_b = (const Entity *)b;

  return entity_a->render_layer - entity_b->render_layer;
}

Scene *SetupScene() {
  Scene *scene = SDL_malloc(sizeof(Scene));
  SDL_memset(scene, 0, sizeof(Scene));
  return scene;
}

void Imzi_RenderScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time) {
  qsort(scene->entities, scene->entity_count, sizeof(Entity),
        compare_render_layer);
  for (int32_t i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].id == 0) {
      continue;
    }

    scene->entities[i].renderPtr(engine, scene->entities + i, frame_time);
  }
}

void Imzi_UpdateScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time) {
  for (int32_t i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].id == 0) {
      continue;
    }

    scene->entities[i].updatePtr(engine, scene->entities + i, frame_time);
  }

  Imzi_RemoveMarkedEntitiesFromScene(scene);
}

Entity *Imzi_FindEntityInScene(Scene *scene, uint32_t entity_id) {
  if (scene->entity_count == 0) {
    return NULL;
  }

  for (int i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].id == entity_id) {
      return scene->entities + i;
    }
  }

  return NULL;
}

Entity *Imzi_AddEntityToScene(Scene *scene) {
  if (scene->entity_count >= MAX_SCENE_ENTITIES) {
    return NULL;
  }

  Entity *entity = scene->entities + scene->entity_count;
  scene->entity_count++;
  entity->id = scene->entity_count;

  return entity;
}

/// Avoid, prefer to simply mark the component as deleted and skip when about to
/// process
bool Imzi_RemoveEntityFromScene(Scene *scene, uint32_t entity_id) {
  if (scene->entity_count == 0) {
    return false;
  }

  int32_t index = -1;

  for (int32_t i = 0; i <= scene->entity_count; i++) {
    if (scene->entities[i].id == entity_id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    return false;
  }

  scene->entities[index].id = 0;

  return true;
}

bool Imzi_RemoveMarkedEntitiesFromScene(Scene *scene) {

  if (scene->entity_count == 0) {
    return true;
  }

  int32_t read_index = 0;
  int32_t write_index = 0;

  while (read_index < scene->entity_count) {
    Entity entity = scene->entities[read_index];
    if (entity.id == 0) {
      SDL_free(entity.data);
      read_index++;
      continue;
    }

    if (read_index != write_index) {
      scene->entities[write_index] = entity;
    }

    write_index++;
    read_index++;
  }

  scene->entity_count = write_index;

  return true;
}
