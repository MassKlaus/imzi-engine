#ifndef ENTITIY_H
#define ENTITIY_H

#include <SDL3/SDL.h>
#include <inttypes.h>

typedef struct Entity
{
    void *data;
    void (*updatePtr)(Imzi_Engine_Ptr engine, void *data, double frame_time);
    void (*renderPtr)(Imzi_Engine_Ptr engine, void *data, double frame_time);
    uint32_t id;
} Entity;

#endif