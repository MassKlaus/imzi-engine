#include <SDL3_image/SDL_image.h>
#include <core/imzi.h>
#include <game/scenes/test_scene.h>

Imzi_Context_Ptr GlobalContext;

Imzi_Context_Ptr Imzi_Init(const char *title, int width, int height) {
  Imzi_Context_Ptr ctx = SDL_malloc(sizeof(Imzi_Context));
  memset(ctx, 0, sizeof(Imzi_Context));

  GlobalContext = ctx;
  ctx->x = 0;
  ctx->y = 0;
  ctx->height = height;
  ctx->width = width;
  ctx->title = title;
  ctx->close_key = SDLK_ESCAPE;
  ctx->should_close = false;

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return NULL;
  }

  const bool succeeded = SDL_CreateWindowAndRenderer(
      title, ctx->width, ctx->height, SDL_WINDOW_BORDERLESS, &ctx->window,
      &ctx->renderer);

  if (!succeeded) {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    return NULL;
  }

  return ctx;
}

void Imzi_Deinit(Imzi_Context_Ptr ctx) {
  if (ctx->renderer)
    SDL_DestroyRenderer(ctx->renderer);

  if (ctx->window)
    SDL_DestroyWindow(ctx->window);
}

bool Imzi_ShouldClose(Imzi_Context_Ptr ctx) { return ctx->should_close; }
