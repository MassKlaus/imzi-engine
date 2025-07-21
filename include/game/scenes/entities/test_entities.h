#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H


#include <SDL3_image/SDL_image.h>
#include <cglm/cglm.h>
#include "engine/entity.h"
#include "engine/players/animation_player.h"
#include "engine/visuals/tilemap.h"

typedef struct 
{
    AnimationPlayer animation_player;
    TileMap* map;
    vec2 position;
    vec2 velocity;
} TestEntityData;

Entity SetupTestEntity(Imzi_Engine_Ptr engine);

void UpdateTestEntity(Imzi_Engine_Ptr engine, void* entity, double frame_time);
void RenderTestEntity(Imzi_Engine_Ptr engine, void* entity, double frame_time);

#endif