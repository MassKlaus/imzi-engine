
#include "engine/engine.h"
#include "engine/entity.h"
#include "engine/scene.h"

void Imzi_RenderScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time)
{
    for (int32_t i = 0; i < scene->entity_count; i++)
    {
        const Entity entity = scene->entities[i];

        entity.renderPtr(engine, entity.data, frame_time);
    }
}

void Imzi_UpdateScene(Imzi_Engine_Ptr engine, Scene *scene, double frame_time)
{
    for (int32_t i = 0; i < scene->entity_count; i++)
    {
        const Entity entity = scene->entities[i];

        entity.updatePtr(engine, entity.data, frame_time);
    }
}


bool Imzi_AddEntityToScene(Scene *scene, Entity entity)
{
    if (scene->entity_count >= MAX_SCENE_ENTITIES)
    {
        return false;
    }

    entity.id = scene->entity_count;
    scene->entities[scene->entity_count] = entity;
    scene->entity_count++;

    return true;
}