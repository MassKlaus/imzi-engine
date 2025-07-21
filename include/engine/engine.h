#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include "core/imzi.h"

typedef struct
{
    Imzi_Context_Ptr ctx;
    void* game_data;
    uint64_t new_time;    
    uint64_t old_time;    
} Imzi_Engine;

typedef Imzi_Engine* Imzi_Engine_Ptr;

Imzi_Engine_Ptr Imzi_InitEngine(const char* title, int width, int height);

#endif