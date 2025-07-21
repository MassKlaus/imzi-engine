#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <inttypes.h>
#include <cglm/cglm.h>
#include "engine/visuals/sprite_sheet.h"

typedef struct
{
    char name[64];
    SDL_FRect area;
    int32_t sprite_sheet_index;
} Sprite;

#endif