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

int32_t Imzi_AssetManager2DLoadSpriteSheet(AssetManager2D *manager,
                                           const char *path) {
  if (manager->sprite_sheet_count == MAX_ASSET_COUNT) {
    return -1;
  }

  SpriteSheet *sprite_sheet =
      manager->sprite_sheets + manager->sprite_sheet_count;

  Imzi_LoadSpriteSheet(path, sprite_sheet);

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

int32_t Imzi_AssetManager2DGetOrLoadSpriteSheet(AssetManager2D *manager,
                                                const char *path) {
  int32_t sheet_index = Imzi_AssetManager2DGetSpriteSheet(manager, path);

  if (sheet_index == -1) {
    sheet_index = Imzi_AssetManager2DLoadSpriteSheet(manager, path);
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

  SpriteSheet *sheet = manager->sprite_sheets + sprite_sheet_index;

  // Calculate UV coordinates
  float u1, v1, u2, v2;
  if (area == NULL) {
    // Use entire texture
    sprite->size[0] = sheet->texture.w;
    sprite->size[1] = sheet->texture.h;
    u1 = 0.0f;
    v1 = 1.0f;
    u2 = 1.0f;
    v2 = 0.0f;
  } else {
    // Use specified area
    sprite->size[0] = area->w;
    sprite->size[1] = area->h;
    u1 = area->x / sheet->texture.w;
    v1 = area->y / sheet->texture.h;
    v1 = (area->y + area->h) / sheet->texture.h;
    u2 = (area->x + area->w) / sheet->texture.w;
    v2 = area->y / sheet->texture.h;
  }

  float vertices[] = {
      0.0f, 0.0f, u1, v2, // Bottom-left
      1.0f, 0.0f, u2, v2, // Bottom-right
      0.0f, 1.0f, u1, v1, // Top-left
      1.0f, 1.0f, u2, v1, // Top-right
  };

  GLuint vao = 0;
  GLuint vbo = 0;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // remembers the state of links between vao and other data
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  sprite->vao = vao;
  manager->sprite_count++;

  return manager->sprite_count - 1;
}

int32_t Imzi_AssetManager2DCreateSpriteFromPath(AssetManager2D *manager,
                                                const char *path,
                                                const char *name,
                                                SDL_FRect *area) {
  int32_t sprite_sheet_index =
      Imzi_AssetManager2DGetOrLoadSpriteSheet(manager, path);

  if (sprite_sheet_index == -1) {
    return -1;
  }

  return Imzi_AssetManager2DCreateSprite(manager, sprite_sheet_index, name,
                                         area);
}

int32_t Imzi_AssetManager2DCreateAnimation(AssetManager2D *manager,
                                           int32_t sprite_sheet_index,
                                           const char *name, SDL_FRect *area,
                                           float frame_w, float frame_h,
                                           int32_t frame_count,
                                           double frame_time, bool loop) {
  if (manager->animation_count == MAX_ASSET_COUNT) {
    return -1;
  }

  Animation *animation = manager->animations + manager->animation_count;
  animation->sprite_sheet_index = sprite_sheet_index;
  animation->frame_w = frame_w;
  animation->frame_h = frame_h;
  animation->frame_time = frame_time;
  animation->frame_count = frame_count;
  animation->loop = loop;
  SDL_strlcpy(animation->name, name, 64);

  SpriteSheet *sheet = manager->sprite_sheets + sprite_sheet_index;

  // Calculate UV coordinates for the first frame
  float u1, v1, u2, v2;
  if (area == NULL) {
    // Use entire texture width, but only one frame height
    animation->size[0] = frame_w;
    animation->size[1] = frame_h;
    u1 = 0.0f;
    v1 = 0.0f;
    u2 = frame_w / sheet->texture.w;
    v2 = frame_h / sheet->texture.h;
  } else {
    // Use specified area for the first frame
    animation->size[0] = frame_w;
    animation->size[1] = frame_h;
    u1 = area->x / sheet->texture.w;
    v1 = area->y / sheet->texture.h;
    u2 = (area->x + frame_w) / sheet->texture.w;
    v2 = (area->y + frame_h) / sheet->texture.h;
  }

  // Store UV step for frame shifting
  animation->uv_step = frame_w / sheet->texture.w;

  // Create vertices for the first frame (UV shifting will handle the rest)
  float vertices[] = {
      0.0f, 0.0f, u1, v1, // Bottom-left
      1.0f, 0.0f, u2, v1, // Bottom-right
      0.0f, 1.0f, u1, v2, // Top-left
      1.0f, 1.0f, u2, v2, // Top-right
  };

  GLuint vao = 0;
  GLuint vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  animation->vao = vao;
  manager->animation_count++;
  return manager->animation_count - 1;
}

int32_t Imzi_AssetManager2DCreateAnimationFromPath(
    AssetManager2D *manager, const char *path, const char *name,
    SDL_FRect *area, float frame_h, float frame_w, int32_t frame_count,
    double frame_time, bool loop) {

  int32_t sprite_sheet_index =
      Imzi_AssetManager2DGetOrLoadSpriteSheet(manager, path);

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
