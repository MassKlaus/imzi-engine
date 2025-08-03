#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "core/graphics/texture.h"
#include <SDL3/SDL.h>

typedef struct {
  char name[64];
  Imzi_Texture texture;
} SpriteSheet;

void Imzi_LoadSpriteSheet(const char *name, SpriteSheet *sheet);

void Imzi_UnloadSpriteSheet(SpriteSheet *sprite_sheet);

#endif
