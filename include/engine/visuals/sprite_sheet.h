#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "core/graphics/texture.h"
#include "engine/engine.h"
#include <SDL3/SDL.h>

typedef struct {
  char name[64];
  Imzi_Texture *texture;
} SpriteSheet;

SpriteSheet *Imzi_LoadSpriteSheet(Imzi_Engine_Ptr engine, const char *name);
void Imzi_UnloadSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet);

void Imzi_RenderPartialSpriteSheet(Imzi_Engine_Ptr engine,
                                   SpriteSheet *sprite_sheet, SDL_FRect *src,
                                   SDL_FRect *dest);
void Imzi_RenderPartialSpriteSheetStatic(Imzi_Engine_Ptr engine,
                                         SpriteSheet *sprite_sheet,
                                         SDL_FRect *src, SDL_FRect *dest);

void Imzi_RenderPartialSpriteSheetEx(Imzi_Engine_Ptr engine,
                                     SpriteSheet *sprite_sheet, SDL_FRect *src,
                                     SDL_FRect *dest, SDL_FlipMode flip);
void Imzi_RenderPartialSpriteSheetExWithOffset(Imzi_Engine_Ptr engine,
                                               SpriteSheet *sprite_sheet,
                                               SDL_FRect *src, SDL_FRect *dest,
                                               SDL_FlipMode flip,
                                               vec2 render_offset);

void Imzi_RenderPartialSpriteSheetExStatic(Imzi_Engine_Ptr engine,
                                           SpriteSheet *sprite_sheet,
                                           SDL_FRect *src, SDL_FRect *dest,
                                           SDL_FlipMode flip);
#endif
