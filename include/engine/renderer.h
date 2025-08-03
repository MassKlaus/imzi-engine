#ifndef RENDERER_H
#define RENDERER_H

#include "SDL3/SDL_surface.h"
#include "cglm/types.h"
#include "core/imzi.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/visuals/sprite.h"
#include <SDL3/SDL.h>
#include <stdint.h>

typedef struct {
  Imzi_Context ctx;
  AssetManager2D manager;
  mat4 camera_matrix;
  vec2 render_shift;
  SDL_GLContext renderContext;
  GLuint spriteShader;
  GLuint animationShader;
} Imzi_Renderer;

typedef Imzi_Renderer *Imzi_Renderer_Ptr;

void Imzi_InitRenderer(const char *title, int width, int height,
                       Imzi_Renderer_Ptr renderer);

void Imzi_DeinitRenderer(Imzi_Renderer_Ptr renderer);

void Imzi_RendererDrawStaticSprite(Imzi_Renderer_Ptr renderer,
                                   int32_t sprite_index, vec2 position);

void Imzi_RendererDrawStaticSpriteTo(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_index, SDL_FRect *area);

void Imzi_RendererDrawSprite(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                             vec2 position);

void Imzi_RendererDrawSpriteTo(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                               SDL_FRect *area);

void Imzi_RendererDrawAnimationFrame(Imzi_Renderer_Ptr renderer,
                                     int32_t animation_index, uint frame,
                                     vec2 position, SDL_FlipMode mode);

void Imzi_RendererDrawAnimationFrameTo(Imzi_Renderer_Ptr renderer,
                                       int32_t animation_index, uint frame,
                                       SDL_FRect *dest, SDL_FlipMode mode);

void Imzi_RendererDrawStaticAnimationFrame(Imzi_Renderer_Ptr renderer,
                                           int32_t animation_index, uint frame,
                                           vec2 position, SDL_FlipMode mode);

void Imzi_RendererDrawStaticAnimationFrameTo(Imzi_Renderer_Ptr renderer,
                                             int32_t animation_index,
                                             uint frame, SDL_FRect *dest,
                                             SDL_FlipMode mode);

// ====================== Shortcut to Handle AssetManager ===============

int32_t Imzi_RendererLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                     const char *path);

int32_t Imzi_RendererGetSpriteSheet(Imzi_Renderer_Ptr renderer,
                                    const char *path);

int32_t Imzi_RendererGetOrLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                          const char *path);

int32_t Imzi_RendererCreateSpriteFromPath(Imzi_Renderer_Ptr renderer,
                                          const char *path, const char *name,
                                          SDL_FRect *area);
int32_t Imzi_RendererCreateSprite(Imzi_Renderer_Ptr renderer,
                                  int32_t sprite_sheet_index, const char *name,
                                  SDL_FRect *area);

int32_t Imzi_RendererGetSpriteByName(Imzi_Renderer_Ptr renderer,
                                     const char *name);

int32_t Imzi_RendererCreateAnimationFromPath(Imzi_Renderer_Ptr renderer,
                                             const char *path, const char *name,
                                             SDL_FRect *area, float frame_h,
                                             float frame_w, int32_t frame_count,
                                             double frame_time, bool loop);

int32_t Imzi_RendererCreateAnimation(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_sheet_index,
                                     const char *name, SDL_FRect *area,
                                     float frame_h, float frame_w,
                                     int32_t frame_count, double frame_time,
                                     bool loop);

int32_t Imzi_RendererGetAnimationByName(Imzi_Renderer_Ptr renderer,
                                        const char *name);

#endif
