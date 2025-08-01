#ifndef IMZI_H
#define IMZI_H

#include <SDL3/SDL.h>

typedef SDL_Renderer Imzi_Renderer;
typedef SDL_Window Imzi_Window;

typedef struct Imzi_Context {
  // X, Y inside the window. This allow us to create mini rendering pockets.
  Imzi_Window *window;
  Imzi_Renderer *renderer;
  const char *title;
  int close_key; // If clicked, this will automatically close the window;
  int x, y, height, width;
  bool should_close;

  char last_input[10]; // Will need me to detail what key is what but it's a
                       // good start
  char current_input[10];
} Imzi_Context;

typedef Imzi_Context *Imzi_Context_Ptr;

void Imzi_Init(Imzi_Context_Ptr ctx, const char *title, int width, int height);
bool Imzi_ShouldClose(Imzi_Context_Ptr ctx);
void Imzi_Deinit(Imzi_Context_Ptr ctx);

#endif
