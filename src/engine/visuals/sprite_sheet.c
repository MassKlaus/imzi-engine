
#include <SDL3_image/SDL_image.h>
#include "engine/visuals/sprite_sheet.h"

SpriteSheet *Imzi_LoadSpriteSheet(Imzi_Engine_Ptr engine, const char *name)
{
    SpriteSheet* sheet = SDL_malloc(sizeof(SpriteSheet));
    sheet->texture = IMG_LoadTexture(engine->ctx->renderer, name);
    return sheet;
}

void Imzi_UnloadSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet)
{
    (void)engine;
    SDL_DestroyTexture(sprite_sheet->texture);
}

void Imzi_RenderPartialSpriteSheet(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet, SDL_FRect *src, SDL_FRect *dest)
{
    Imzi_RenderPartialSpriteSheetEx(engine, sprite_sheet, src, dest, SDL_FLIP_NONE);
}

void Imzi_RenderPartialSpriteSheetEx(Imzi_Engine_Ptr engine, SpriteSheet *sprite_sheet, SDL_FRect *src, SDL_FRect *dest, SDL_FlipMode flip)
{
    SDL_RenderTextureRotated(engine->ctx->renderer, sprite_sheet->texture, src, dest, 0, NULL, flip);
}