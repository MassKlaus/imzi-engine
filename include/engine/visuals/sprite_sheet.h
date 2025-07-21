#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SDL3/SDL.h>
#include "core/graphics/texture.h"
#include "engine/engine.h"

typedef struct {
    char name[64];
    Imzi_Texture* texture;
} SpriteSheet;

SpriteSheet *Imzi_LoadSpriteSheet(Imzi_Engine_Ptr engine, const char *name);
void Imzi_UnloadSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet);

void Imzi_RenderPartialSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet, SDL_FRect *src, SDL_FRect *dest);
void Imzi_RenderPartialSpriteSheetEx(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet, SDL_FRect *src, SDL_FRect *dest, SDL_FlipMode flip);



#endif