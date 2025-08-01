#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include "engine/engine.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/renderer.h"
#include <inttypes.h>

typedef struct {
  double elapsed_frame_time;
  int32_t animation_index;

  bool paused;
  bool h_flip;
  bool v_flip;
} AnimationPlayer;

AnimationPlayer Imzi_SetupAnimationPlayer(int32_t animation_id);

void Imzi_StartAnimationPlayer(AnimationPlayer *player,
                               int32_t animation_index);

void Imzi_StartAnimationPlayerByName(Imzi_Renderer_Ptr renderer,
                                     AnimationPlayer *player, const char *name);

void Imzi_UpdateAnimationPlayer(AnimationPlayer *player, double delta_time);

void Imzi_AnimationPlayerRender(Imzi_Renderer_Ptr renderer,
                                AnimationPlayer *player, vec2 position);

int32_t Imzi_GetCurrentAnimationFrame(Imzi_Renderer_Ptr renderer,
                                      AnimationPlayer *player);

#endif
