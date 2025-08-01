#ifndef ASSET_MANAGER_2D_H
#define ASSET_MANAGER_2D_H

#include "engine/visuals/animation.h"
#include "engine/visuals/sprite.h"
#include "engine/visuals/sprite_sheet.h"

#define MAX_ASSET_COUNT 100

typedef struct {
  SpriteSheet sprite_sheets[MAX_ASSET_COUNT];
  int32_t sprite_sheet_count;

  Sprite sprites[MAX_ASSET_COUNT];
  int32_t sprite_count;

  Animation animations[MAX_ASSET_COUNT];
  int32_t animation_count;
} AssetManager2D;

// Rendering system will encapsulate the different assets we need and use them
// as we need

void Imzi_SetupAssetManager2D(AssetManager2D *manager);

int32_t Imzi_AssetManager2DLoadSpriteSheet(Imzi_Context_Ptr ctx,
                                           AssetManager2D *manager,
                                           const char *path);

int32_t Imzi_AssetManager2DGetSpriteSheet(AssetManager2D *manager,
                                          const char *path);

int32_t Imzi_AssetManager2DGetOrLoadSpriteSheet(Imzi_Context_Ptr ctx,
                                                AssetManager2D *manager,
                                                const char *path);

int32_t Imzi_AssetManager2DCreateSpriteFromPath(Imzi_Context_Ptr ctx,
                                                AssetManager2D *manager,
                                                const char *path,
                                                const char *name,
                                                SDL_FRect *area);
int32_t Imzi_AssetManager2DCreateSprite(AssetManager2D *manager,
                                        int32_t sprite_sheet_index,
                                        const char *name, SDL_FRect *area);

int32_t Imzi_AssetManager2DGetSpriteByName(AssetManager2D *manager,
                                           const char *name);

int32_t Imzi_AssetManager2DCreateAnimationFromPath(
    Imzi_Context_Ptr ctx, AssetManager2D *manager, const char *path,
    const char *name, SDL_FRect *area, float frame_h, float frame_w,
    int32_t frame_count, double frame_time, bool loop);

int32_t Imzi_AssetManager2DCreateAnimation(AssetManager2D *manager,
                                           int32_t sprite_sheet_index,
                                           const char *name, SDL_FRect *area,
                                           float frame_h, float frame_w,
                                           int32_t frame_count,
                                           double frame_time, bool loop);

int32_t Imzi_AssetManager2DGetAnimationByName(AssetManager2D *manager,
                                              const char *name);

#endif
