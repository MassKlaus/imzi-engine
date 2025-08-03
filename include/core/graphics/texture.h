#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include <SDL3/SDL.h>

typedef struct {
  int w; /**< The width of the texture, read-only. */
  int h; /**< The height of the texture, read-only. */
  GLuint id;
} Imzi_Texture;

#endif
