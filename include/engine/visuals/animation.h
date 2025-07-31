#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL3/SDL.h>
#include <inttypes.h>

typedef struct {
  char name[64];
  double frame_time;
  float frame_w, frame_h;
  SDL_FRect area;
  int32_t sprite_sheet_index, frame_count;
  bool loop;
} Animation;

#endif
