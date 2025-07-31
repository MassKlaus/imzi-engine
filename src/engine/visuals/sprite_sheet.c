
#include "engine/visuals/sprite_sheet.h"
#include "cglm/types.h"
#include <SDL3_image/SDL_image.h>

SpriteSheet *Imzi_LoadSpriteSheet(Imzi_Engine_Ptr engine, const char *name) {
  SpriteSheet *sheet = SDL_malloc(sizeof(SpriteSheet));
  sheet->texture = IMG_LoadTexture(engine->ctx->renderer, name);
  return sheet;
}

void Imzi_UnloadSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet) {
  (void)engine;
  SDL_DestroyTexture(sprite_sheet->texture);
}

void Imzi_RenderPartialSpriteSheet(Imzi_Engine_Ptr engine,
                                   SpriteSheet *sprite_sheet, SDL_FRect *src,
                                   SDL_FRect *dest) {
  Imzi_RenderPartialSpriteSheetEx(engine, sprite_sheet, src, dest,
                                  SDL_FLIP_NONE);
}

void Imzi_RenderPartialSpriteSheetStatic(Imzi_Engine_Ptr engine,
                                         SpriteSheet *sprite_sheet,
                                         SDL_FRect *src, SDL_FRect *dest) {
  Imzi_RenderPartialSpriteSheetExStatic(engine, sprite_sheet, src, dest,
                                        SDL_FLIP_NONE);
}

void Imzi_RenderPartialSpriteSheetEx(Imzi_Engine_Ptr engine,
                                     SpriteSheet *sprite_sheet, SDL_FRect *src,
                                     SDL_FRect *dest, SDL_FlipMode flip) {
  Imzi_RenderPartialSpriteSheetExWithOffset(engine, sprite_sheet, src, dest,
                                            flip, engine->render_offset);
}

void Imzi_RenderPartialSpriteSheetExStatic(Imzi_Engine_Ptr engine,
                                           SpriteSheet *sprite_sheet,
                                           SDL_FRect *src, SDL_FRect *dest,
                                           SDL_FlipMode flip) {
  Imzi_RenderPartialSpriteSheetExWithOffset(engine, sprite_sheet, src, dest,
                                            flip, (vec2){0, 0});
}

void Imzi_RenderPartialSpriteSheetExWithOffset(Imzi_Engine_Ptr engine,
                                               SpriteSheet *sprite_sheet,
                                               SDL_FRect *src, SDL_FRect *dest,
                                               SDL_FlipMode flip,
                                               vec2 render_offset) {
  SDL_FRect final_position =
      (SDL_FRect){(dest->x - render_offset[0]), (dest->y - render_offset[1]),
                  dest->w, dest->h};
  SDL_RenderTextureRotated(engine->ctx->renderer, sprite_sheet->texture, src,
                           &final_position, 0, NULL, flip);
}
