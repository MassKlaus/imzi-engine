#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <glad/glad.h>
#include <inttypes.h>

typedef struct {
  char name[64];
  vec2 size;
  GLuint vao;
  int32_t sprite_sheet_index;
} Sprite;

#endif
