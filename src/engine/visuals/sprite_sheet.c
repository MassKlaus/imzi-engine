
#include "engine/visuals/sprite_sheet.h"
#include "core/imzi.h"
#include <SDL3_image/SDL_image.h>

void Imzi_LoadSpriteSheet(Imzi_Context_Ptr ctx, const char *name,
                          SpriteSheet *sheet) {
  sheet->texture = IMG_LoadTexture(ctx->renderContext, name);
}

void Imzi_UnloadSpriteSheet(SpriteSheet *sprite_sheet) {
  SDL_DestroyTexture(sprite_sheet->texture);
}
