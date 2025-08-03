#ifndef ANIMATION_H
#define ANIMATION_H

#include "cglm/types.h"
#include "glad/glad.h"
#include <SDL3/SDL.h>
#include <inttypes.h>

typedef struct {
  char name[64];
  double frame_time;
  float frame_w, frame_h;
  int32_t sprite_sheet_index, frame_count;
  vec2 size;
  float uv_step; // How much to shift UV per frame
  GLuint vao;
  bool loop;
} Animation;

#endif
