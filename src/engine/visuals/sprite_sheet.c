
#include "engine/visuals/sprite_sheet.h"
#include "core/imzi.h"
#include <SDL3_image/SDL_image.h>

void Imzi_LoadSpriteSheet(Imzi_Context_Ptr ctx, const char *name,
                          SpriteSheet *sheet) {
  sheet->texture = IMG_LoadTexture(ctx->renderer, name);
}

void Imzi_UnloadSpriteSheet(SpriteSheet *sprite_sheet) {
  SDL_DestroyTexture(sprite_sheet->texture);
}

void Imzi_RenderPartialSpriteSheet(Imzi_Context_Ptr ctx,
                                   SpriteSheet *sprite_sheet, SDL_FRect *src,
                                   SDL_FRect *dest) {
  Imzi_RenderPartialSpriteSheetEx(ctx, sprite_sheet, src, dest, SDL_FLIP_NONE);
}

void Imzi_RenderPartialSpriteSheetEx(Imzi_Context_Ptr ctx,
                                     SpriteSheet *sprite_sheet, SDL_FRect *src,
                                     SDL_FRect *dest, SDL_FlipMode flip) {
  SDL_RenderTextureRotated(ctx->renderer, sprite_sheet->texture, src, dest, 0,
                           NULL, flip);
}
