#ifndef IMZI_H
#define IMZI_H

#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>

typedef struct Imzi_Context {
  // X, Y inside the window. This allow us to create mini rendering pockets.
  SDL_Window *window;
  SDL_Renderer *renderContext;
  const char *title;
  int close_key; // If clicked, this will automatically close the window;
  int x, y, height, width;
  bool should_close;

  char last_input[10]; // Will need me to detail what key is what but it's a
                       // good start
  char current_input[10];
} Imzi_Context;

typedef Imzi_Context *Imzi_Context_Ptr;

void Imzi_Init(const char *title, int width, int height, Imzi_Context_Ptr ctx);
bool Imzi_ShouldClose(Imzi_Context_Ptr ctx);
void Imzi_Deinit(Imzi_Context_Ptr ctx);

#endif
