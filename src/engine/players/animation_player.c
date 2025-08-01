#include <SDL3/SDL.h>
#include <inttypes.h>

#include "engine/managers/asset_manager_2d.h"
#include "engine/players/animation_player.h"

AnimationPlayer Imzi_SetupAnimationPlayer(int32_t animation_index) {
  AnimationPlayer player = {0};
  player.animation_index = animation_index;
  player.elapsed_frame_time = 0;
  player.h_flip = false;
  player.v_flip = false;
  player.paused = false;

  return player;
}

void Imzi_StartAnimationPlayerByName(AssetManager2D *manager,
                                     AnimationPlayer *player,
                                     const char *name) {
  int32_t animation_index =
      Imzi_AssetManager2DGetAnimationByName(manager, name);
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

void Imzi_AnimationPlayerRender(Imzi_Context_Ptr ctx, AssetManager2D *manager,
                                AnimationPlayer *player, vec2 position) {
  Animation *animation = manager->animations + player->animation_index;
  SpriteSheet *sheet = manager->sprite_sheets + animation->sprite_sheet_index;

  int32_t frame = Imzi_GetCurrentAnimationFrame(manager, player);

  SDL_FRect src = {animation->area.x + animation->frame_w * frame,
                   animation->area.y, animation->frame_w, animation->frame_h};
  // SDL_FRect src = {0, 0, 64.0, 64.0};
  SDL_FRect dest = {position[0], position[1], animation->area.w,
                    animation->area.h};
  // SDL_FRect dest = {0, 0, 64.0, 64.0};

  SDL_FlipMode flip = SDL_FLIP_NONE;

  if (player->h_flip)
    flip |= SDL_FLIP_HORIZONTAL;
  if (player->v_flip)
    flip |= SDL_FLIP_VERTICAL;

  Imzi_RenderPartialSpriteSheetEx(ctx, sheet, &src, &dest, flip);
}

void Imzi_UpdateAnimationPlayer(AnimationPlayer *player, double delta_time) {
  if (player->paused) {
    return;
  }

  player->elapsed_frame_time += delta_time;
}

int32_t Imzi_GetCurrentAnimationFrame(AssetManager2D *manager,
                                      AnimationPlayer *player) {
  Animation *animation = manager->animations + player->animation_index;

  int32_t frame = (player->elapsed_frame_time / animation->frame_time);

  if (animation->loop) {
    frame = frame % animation->frame_count;
  } else {
    frame = SDL_min(frame, animation->frame_count - 1);
  }

  return frame;
}
