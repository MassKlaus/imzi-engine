#include <SDL3/SDL.h>
#include <inttypes.h>

#include "engine/players/animation_player.h"
#include "engine/visuals/render.h"

AnimationPlayer Imzi_SetupAnimationPlayer(AssetManager2D *manager,
                                          int32_t animation_index) {
  AnimationPlayer player = {0};
  player.manager = manager;
  player.animation_index = animation_index;
  player.elapsed_frame_time = 0;
  player.h_flip = false;
  player.v_flip = false;
  player.paused = false;

  return player;
}

void Imzi_StartAnimationPlayerByName(AnimationPlayer *player,
                                     const char *name) {
  int32_t animation_index =
      Imzi_AssetManager2DGetAnimationByName(player->manager, name);
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

void Imzi_AnimationPlayerRender(Imzi_Engine_Ptr engine, AnimationPlayer *player,
                                vec2 position) {
  AssetManager2D *manager = player->manager;

  Animation *animation = manager->animations[player->animation_index];
  SpriteSheet *sheet = manager->sprite_sheets[animation->sprite_sheet_index];

  int32_t frame = Imzi_GetCurrentAnimationFrame(player);

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

  Imzi_RenderPartialSpriteSheetEx(engine, sheet, &src, &dest, flip);
}

void Imzi_UpdateAnimationPlayer(AnimationPlayer *player, double delta_time) {
  if (player->paused) {
    return;
  }

  Animation *animation = player->manager->animations[player->animation_index];
  if (animation == NULL) {
    return;
  }

  player->elapsed_frame_time += delta_time;
}

int32_t Imzi_GetCurrentAnimationFrame(AnimationPlayer *player) {
  AssetManager2D *manager = player->manager;

  Animation *animation = manager->animations[player->animation_index];

  int32_t frame = (player->elapsed_frame_time / animation->frame_time);

  if (animation->loop) {
    frame = frame % animation->frame_count;
  } else {
    frame = SDL_min(frame, animation->frame_count - 1);
  }

  return frame;
}
