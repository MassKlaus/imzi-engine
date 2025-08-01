#include "engine/renderer.h"
#include "SDL3/SDL_assert.h"
#include "core/imzi.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/visuals/sprite_sheet.h"

void Imzi_InitRenderer(const char *title, int width, int height,
                       Imzi_Renderer_Ptr renderer) {
  Imzi_Init(title, width, height, &renderer->ctx);
}

void Imzi_DeinitRenderer(Imzi_Renderer_Ptr renderer) {
  Imzi_Deinit(&renderer->ctx);
}

void Imzi_RendererDrawStaticSprite(Imzi_Renderer_Ptr renderer,
                                   int32_t sprite_index, vec2 position) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;

  SDL_FRect src = {sprite->area.x, sprite->area.y, sprite->area.w,
                   sprite->area.h};
  SDL_FRect dest = {position[0], position[1], sprite->area.w, sprite->area.h};

  Imzi_RendererDrawPartialSpriteSheet(renderer, sprite->sprite_sheet_index,
                                      &src, &dest);
}

void Imzi_RendererDrawStaticSpriteTo(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_index, SDL_FRect *area) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;

  SDL_FRect src = {sprite->area.x, sprite->area.y, sprite->area.w,
                   sprite->area.h};

  SDL_FRect dest = {area->x + renderer->render_offset[0],
                    area->y + renderer->render_offset[1], area->w, area->h};

  Imzi_RendererDrawPartialSpriteSheet(renderer, sprite->sprite_sheet_index,
                                      &src, &dest);
}

void Imzi_RendererDrawSprite(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                             vec2 position) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;

  // SDL_Log("X:%f Y:%f", renderer->render_offset[0],
  // renderer->render_offset[1]);
  SDL_FRect dest = {position[0], position[1], sprite->area.w, sprite->area.h};

  Imzi_RendererDrawPartialSpriteSheet(renderer, sprite->sprite_sheet_index,
                                      &sprite->area, &dest);
}

void Imzi_RendererDrawSpriteTo(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                               SDL_FRect *area) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;
  SDL_FRect src = {sprite->area.x, sprite->area.y, sprite->area.w,
                   sprite->area.h};

  Imzi_RendererDrawPartialSpriteSheet(renderer, sprite->sprite_sheet_index,
                                      &src, area);
}

void Imzi_RendererDrawPartialSpriteSheet(Imzi_Renderer_Ptr renderer,
                                         int32_t sprite_sheet_index,
                                         SDL_FRect *src, SDL_FRect *dest) {
  Imzi_RendererDrawPartialSpriteSheetEx(renderer, sprite_sheet_index, src, dest,
                                        SDL_FLIP_NONE);
}

void Imzi_RendererDrawPartialSpriteSheetEx(Imzi_Renderer_Ptr renderer,
                                           int32_t sprite_sheet_index,
                                           SDL_FRect *src, SDL_FRect *dest,
                                           SDL_FlipMode flip) {
  SDL_assert(renderer->manager.sprite_sheet_count > sprite_sheet_index);
  SpriteSheet *sprite_sheet =
      renderer->manager.sprite_sheets + sprite_sheet_index;

  SDL_FRect final_dest = {dest->x - renderer->render_offset[0],
                          dest->y - renderer->render_offset[1], dest->w,
                          dest->h};

  SDL_RenderTextureRotated(renderer->ctx.renderContext, sprite_sheet->texture,
                           src, &final_dest, 0, NULL, flip);
}

// ======================================================================

int32_t Imzi_RendererLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                     const char *path) {
  return Imzi_AssetManager2DLoadSpriteSheet(&renderer->ctx, &renderer->manager,
                                            path);
}

int32_t Imzi_RendererGetSpriteSheet(Imzi_Renderer_Ptr renderer,
                                    const char *path) {
  return Imzi_AssetManager2DGetSpriteSheet(&renderer->manager, path);
}

int32_t Imzi_RendererGetOrLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                          const char *path) {
  return Imzi_AssetManager2DGetOrLoadSpriteSheet(&renderer->ctx,
                                                 &renderer->manager, path);
}

int32_t Imzi_RendererCreateSpriteFromPath(Imzi_Renderer_Ptr renderer,
                                          const char *path, const char *name,
                                          SDL_FRect *area) {
  return Imzi_AssetManager2DCreateSpriteFromPath(
      &renderer->ctx, &renderer->manager, path, name, area);
}

int32_t Imzi_RendererCreateSprite(Imzi_Renderer_Ptr renderer,
                                  int32_t sprite_sheet_index, const char *name,
                                  SDL_FRect *area) {
  return Imzi_AssetManager2DCreateSprite(&renderer->manager, sprite_sheet_index,
                                         name, area);
}

int32_t Imzi_RendererGetSpriteByName(Imzi_Renderer_Ptr renderer,
                                     const char *name) {
  return Imzi_AssetManager2DGetSpriteByName(&renderer->manager, name);
}

int32_t Imzi_RendererCreateAnimationFromPath(Imzi_Renderer_Ptr renderer,
                                             const char *path, const char *name,
                                             SDL_FRect *area, float frame_h,
                                             float frame_w, int32_t frame_count,
                                             double frame_time, bool loop) {
  return Imzi_AssetManager2DCreateAnimationFromPath(
      &renderer->ctx, &renderer->manager, path, name, area, frame_h, frame_w,
      frame_count, frame_time, loop);
}

int32_t Imzi_RendererCreateAnimation(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_sheet_index,
                                     const char *name, SDL_FRect *area,
                                     float frame_h, float frame_w,
                                     int32_t frame_count, double frame_time,
                                     bool loop) {
  return Imzi_AssetManager2DCreateAnimation(
      &renderer->manager, sprite_sheet_index, name, area, frame_h, frame_w,
      frame_count, frame_time, loop);
}

int32_t Imzi_RendererGetAnimationByName(Imzi_Renderer_Ptr renderer,
                                        const char *name) {
  return Imzi_AssetManager2DGetAnimationByName(&renderer->manager, name);
}
