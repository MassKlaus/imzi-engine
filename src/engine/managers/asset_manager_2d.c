#include "engine/managers/asset_manager_2d.h"
#include "SDL3/SDL_rect.h"
#include "engine/visuals/sprite_sheet.h"
#include <string.h>

void Imzi_SetupAssetManager2D(AssetManager2D *manager) {
  memset(manager, 0, sizeof(AssetManager2D));

  manager->sprite_sheet_count = 0;
  manager->sprite_count = 0;
  manager->animation_count = 0;
}

int32_t Imzi_AssetManager2DLoadSpriteSheet(Imzi_Context_Ptr ctx,
                                           AssetManager2D *manager,
                                           const char *path) {
  if (manager->sprite_sheet_count == MAX_ASSET_COUNT) {
    return -1;
  }

  SpriteSheet *sprite_sheet =
      manager->sprite_sheets + manager->sprite_sheet_count;

  Imzi_LoadSpriteSheet(ctx, path, sprite_sheet);
  SDL_strlcpy(sprite_sheet->name, path, 64);

  manager->sprite_sheet_count += 1;

  return manager->sprite_sheet_count - 1;
}

int32_t Imzi_AssetManager2DGetSpriteSheet(AssetManager2D *manager,
                                          const char *path) {
  for (int32_t i = 0; i < manager->sprite_sheet_count; i++) {
    SpriteSheet *sprite_sheet = manager->sprite_sheets + i;
    if (SDL_strcmp(sprite_sheet->name, path) == 0) {
      return i;
    }
  }

  return -1;
}

int32_t Imzi_AssetManager2DGetOrLoadSpriteSheet(Imzi_Context_Ptr ctx,
                                                AssetManager2D *manager,
                                                const char *path) {
  int32_t sheet_index = Imzi_AssetManager2DGetSpriteSheet(manager, path);

  if (sheet_index == -1) {
    sheet_index = Imzi_AssetManager2DLoadSpriteSheet(ctx, manager, path);
  }

  assert(sheet_index != -1);

  return sheet_index;
}

int32_t Imzi_AssetManager2DCreateSprite(AssetManager2D *manager,
                                        int32_t sprite_sheet_index,
                                        const char *name, SDL_FRect *area) {
  if (manager->sprite_count == MAX_ASSET_COUNT) {
    return -1;
  }

  Sprite *sprite = manager->sprites + manager->sprite_count;
  sprite->sprite_sheet_index = sprite_sheet_index;
  SDL_strlcpy(sprite->name, name, 64);

  if (area == NULL) {
    SpriteSheet *sheet = manager->sprite_sheets + sprite_sheet_index;
    sprite->area = (SDL_FRect){0, 0, sheet->texture->w, sheet->texture->h};
  } else {
    sprite->area = *area;
  }

  manager->sprite_count++;

  return manager->sprite_count - 1;
}

int32_t Imzi_AssetManager2DCreateSpriteFromPath(Imzi_Context_Ptr ctx,
                                                AssetManager2D *manager,
                                                const char *path,
                                                const char *name,
                                                SDL_FRect *area) {
  int32_t sprite_sheet_index =
      Imzi_AssetManager2DGetOrLoadSpriteSheet(ctx, manager, path);

  if (sprite_sheet_index == -1) {
    return -1;
  }

  return Imzi_AssetManager2DCreateSprite(manager, sprite_sheet_index, name,
                                         area);
}

int32_t Imzi_AssetManager2DCreateAnimation(AssetManager2D *manager,
                                           int32_t sprite_sheet_index,
                                           const char *name, SDL_FRect *area,
                                           float frame_h, float frame_w,
                                           int32_t frame_count,
                                           double frame_time, bool loop) {
  if (manager->animation_count == MAX_ASSET_COUNT) {
    return -1;
  }

  assert((frame_w * frame_count) >= area->w);
  assert(frame_h >= area->h);

  Animation *animation = manager->animations + manager->animation_count;
  animation->sprite_sheet_index = sprite_sheet_index;
  animation->frame_h = frame_h;
  animation->frame_w = frame_w;
  animation->frame_time = frame_time;
  animation->frame_count = frame_count;
  animation->loop = loop;

  SDL_strlcpy(animation->name, name, 64);

  if (area == NULL) {
    SpriteSheet *sheet = manager->sprite_sheets + sprite_sheet_index;
    animation->area = (SDL_FRect){0, 0, sheet->texture->w, sheet->texture->h};
  } else {
    animation->area = *area;
  }

  manager->animation_count++;

  return manager->animation_count - 1;
}

int32_t Imzi_AssetManager2DCreateAnimationFromPath(
    Imzi_Context_Ptr ctx, AssetManager2D *manager, const char *path,
    const char *name, SDL_FRect *area, float frame_h, float frame_w,
    int32_t frame_count, double frame_time, bool loop) {

  int32_t sprite_sheet_index =
      Imzi_AssetManager2DGetOrLoadSpriteSheet(ctx, manager, path);

  if (sprite_sheet_index == -1) {
    return -1;
  }

  return Imzi_AssetManager2DCreateAnimation(manager, sprite_sheet_index, name,
                                            area, frame_h, frame_w, frame_count,
                                            frame_time, loop);
}

int32_t Imzi_AssetManager2DGetSpriteByName(AssetManager2D *manager,
                                           const char *name) {
  for (int32_t i = 0; i < manager->sprite_count; i++) {
    Sprite *sprite = manager->sprites + i;
    if (SDL_strcmp(sprite->name, name) == 0) {
      return i;
    }
  }

  return -1;
}

int32_t Imzi_AssetManager2DGetAnimationByName(AssetManager2D *manager,
                                              const char *name) {
  for (int32_t i = 0; i < manager->animation_count; i++) {
    Animation *animation = manager->animations + i;

    if (SDL_strcmp(animation->name, name) == 0) {
      return i;
    }
  }

  return -1;
}
