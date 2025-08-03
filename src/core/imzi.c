#include "core/imzi.h"
#include "SDL3/SDL_video.h"
#include <SDL3_image/SDL_image.h>
#include <game/scenes/test_scene.h>
#include <stdlib.h>

void Imzi_Init(const char *title, int width, int height, Imzi_Context_Ptr ctx) {
  ctx->x = 0;
  ctx->y = 0;
  ctx->height = height;
  ctx->width = width;
  ctx->title = title;
  ctx->close_key = SDLK_ESCAPE;
  ctx->should_close = false;

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    exit(1);
  }

  ctx->window = SDL_CreateWindow(title, ctx->width, ctx->height,
                                 SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);

  if (!ctx->window) {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    exit(1);
  }
}

void Imzi_Deinit(Imzi_Context_Ptr ctx) {
  if (ctx->window)
    SDL_DestroyWindow(ctx->window);
}

bool Imzi_ShouldClose(Imzi_Context_Ptr ctx) { return ctx->should_close; }
