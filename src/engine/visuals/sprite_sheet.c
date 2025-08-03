
#include "engine/visuals/sprite_sheet.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_surface.h"
#include "core/imzi.h"
#include <SDL3_image/SDL_image.h>

void Imzi_LoadSpriteSheet(const char *name, SpriteSheet *sheet) {
  SDL_strlcpy(sheet->name, name, 64);

  SDL_Surface *surface = IMG_Load(name);

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Determine format
  // Determine format - SDL3 surface format handling
  GLenum format;
  GLenum internalFormat;
  if (surface->format == SDL_PIXELFORMAT_RGBA8888 ||
      surface->format == SDL_PIXELFORMAT_ABGR8888) {
    format = GL_RGBA;
    internalFormat = GL_RGBA8;
  } else if (surface->format == SDL_PIXELFORMAT_XRGB8888 ||
             surface->format == SDL_PIXELFORMAT_XBGR8888) {
    format = GL_RGB;
    internalFormat = GL_RGB8;
  } else {
    // Convert to a known format
    SDL_Surface *converted =
        SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
    SDL_DestroySurface(surface);
    surface = converted;
    format = GL_RGBA;
    internalFormat = GL_RGBA8;
  }
  // Upload texture data to GPU
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0,
               format, GL_UNSIGNED_BYTE, surface->pixels);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Store texture info
  sheet->texture.id = textureID;
  sheet->texture.w = surface->w;
  sheet->texture.h = surface->h;

  SDL_DestroySurface(surface);
}

void Imzi_UnloadSpriteSheet(SpriteSheet *sprite_sheet) {
  (void)sprite_sheet;
  // SDL_DestroyTexture(sprite_sheet->texture);
}
