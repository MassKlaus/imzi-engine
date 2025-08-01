#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "core/graphics/texture.h"
#include "core/imzi.h"
#include <SDL3/SDL.h>

typedef struct {
  char name[64];
  Imzi_Texture *texture;
} SpriteSheet;

void Imzi_LoadSpriteSheet(Imzi_Context_Ptr ctx, const char *name,
                          SpriteSheet *sheet);

void Imzi_UnloadSpriteSheet(SpriteSheet *sprite_sheet);

void Imzi_RenderPartialSpriteSheet(Imzi_Context_Ptr ctx,
                                   SpriteSheet *sprite_sheet, SDL_FRect *src,
                                   SDL_FRect *dest);

void Imzi_RenderPartialSpriteSheetEx(Imzi_Context_Ptr ctx,
                                     SpriteSheet *sprite_sheet, SDL_FRect *src,
                                     SDL_FRect *dest, SDL_FlipMode flip);

#endif
