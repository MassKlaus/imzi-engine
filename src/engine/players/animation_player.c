#include <SDL3/SDL.h>
#include <inttypes.h>

#include "engine/managers/asset_manager_2d.h"
#include "engine/players/animation_player.h"
#include "engine/renderer.h"

AnimationPlayer Imzi_SetupAnimationPlayer(int32_t animation_index) {
  AnimationPlayer player = {0};
  player.animation_index = animation_index;
  player.elapsed_frame_time = 0;
  player.h_flip = false;
  player.v_flip = false;
  player.paused = false;

  return player;
}

void Imzi_StartAnimationPlayerByName(Imzi_Renderer_Ptr renderer,
                                     AnimationPlayer *player,
                                     const char *name) {
  int32_t animation_index = Imzi_RendererGetAnimationByName(renderer, name);
  Imzi_StartAnimationPlayer(player, animation_index);
}

void Imzi_StartAnimationPlayer(AnimationPlayer *player,
                               int32_t animation_index) {
  assert(animation_index != -1);

  if (player->animation_index == animation_index) {
    return;
  }

  player->animation_index = animation_index;
  player->elapsed_frame_time = 0;
  player->paused = false;
}

void Imzi_AnimationPlayerRender(Imzi_Renderer_Ptr renderer,
                                AnimationPlayer *player, vec2 position) {
  int32_t frame = Imzi_GetCurrentAnimationFrame(renderer, player);

  SDL_FlipMode flip = SDL_FLIP_NONE;

  if (player->h_flip)
    flip |= SDL_FLIP_HORIZONTAL;
  if (player->v_flip)
    flip |= SDL_FLIP_VERTICAL;

  Imzi_RendererDrawAnimationFrame(renderer, player->animation_index, frame,
                                  position, flip);
}

void Imzi_UpdateAnimationPlayer(AnimationPlayer *player, double delta_time) {
  if (player->paused) {
    return;
  }

  player->elapsed_frame_time += delta_time;
}

int32_t Imzi_GetCurrentAnimationFrame(Imzi_Renderer_Ptr renderer,
                                      AnimationPlayer *player) {

  Animation *animation = renderer->manager.animations + player->animation_index;
  int32_t frame = (player->elapsed_frame_time / animation->frame_time);

  if (animation->loop) {
    frame = frame % animation->frame_count;
  } else {
    frame = SDL_min(frame, animation->frame_count - 1);
  }

  return frame;
}
