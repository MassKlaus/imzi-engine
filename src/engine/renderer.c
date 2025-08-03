#include "engine/renderer.h"
#include "SDL3/SDL_video.h"
#include "cglm/affine-pre.h"
#include "cglm/cam.h"
#include "cglm/mat4.h"
#include "cglm/types.h"
#include "cglm/vec2.h"
#include "core/imzi.h"
#include "engine/managers/asset_manager_2d.h"
#include "engine/visuals/sprite_sheet.h"
#include "glad/glad.h"
#include <stdint.h>

void Imzi_InitRenderer(const char *title, int width, int height,
                       Imzi_Renderer_Ptr renderer) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  Imzi_Init(title, width, height, &renderer->ctx);

  renderer->renderContext = SDL_GL_CreateContext(renderer->ctx.window);

  // 5. Initialize GLAD with SDL's proc address function
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    exit(1);
  }

  const char *vertex =
      "#version 150 core \n"
      "in vec4 vertex; \n"
      "out vec2 TexCoords; \n"
      "uniform mat4 model; \n"
      "uniform mat4 projection; \n"
      "void main() { \n"
      "gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0); \n"
      "TexCoords = vertex.zw; \n"
      "} \n";

  const char *frag = "#version 150 core \n"
                     "in vec2 TexCoords; \n"
                     "out vec4 color; \n"
                     "uniform sampler2D image; \n"
                     "uniform vec3 spriteColor; \n"
                     "void main() \n"
                     "{ \n"
                     "   color = texture(image, TexCoords); \n"
                     "} \n";

  const char *animation_frag =
      "#version 150 core \n"
      "in vec2 TexCoords; \n"
      "out vec4 color; \n"
      "uniform sampler2D image; \n"
      "uniform vec3 spriteColor; \n"
      "uniform float uv_shift; \n"
      "void main() \n"
      "{ \n"
      "   vec2 shiftedUV = vec2(TexCoords.x + uv_shift, TexCoords.y); \n"
      "   color = texture(image, shiftedUV); \n"
      "} \n";

  glm_ortho(0, width, height, 0, -1.0, 1.0, renderer->camera_matrix);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex, NULL);
  glCompileShader(vertexShader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("Vertex shader compilation failed: %s\n", infoLog);
  }

  // Do the same for fragmentShader and animationFragmentShader

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("Vertex shader compilation failed: %s\n", infoLog);
  }

  GLuint animationFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(animationFragmentShader, 1, &animation_frag, NULL);
  glCompileShader(animationFragmentShader);

  glGetShaderiv(animationFragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(animationFragmentShader, 512, NULL, infoLog);
    printf("Vertex shader compilation failed: %s\n", infoLog);
  }

  GLuint spriteProgram = glCreateProgram();
  glAttachShader(spriteProgram, vertexShader);
  glAttachShader(spriteProgram, fragmentShader);

  glBindAttribLocation(spriteProgram, 0, "vertex");
  glBindFragDataLocation(spriteProgram, 0, "color");

  glLinkProgram(spriteProgram);

  glGetProgramiv(spriteProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(spriteProgram, 512, NULL, infoLog);
    printf("Program linking failed: %s\n", infoLog);
  }
  GLuint animationProgram = glCreateProgram();
  glAttachShader(animationProgram, vertexShader);
  glAttachShader(animationProgram, animationFragmentShader);

  glBindAttribLocation(animationProgram, 0, "vertex");
  glBindFragDataLocation(animationProgram, 0, "color");

  glLinkProgram(animationProgram);

  glUseProgram(spriteProgram);
  GLint projLoc = glGetUniformLocation(spriteProgram, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, (float *)renderer->camera_matrix);

  glUseProgram(animationProgram);
  GLint animprojLoc = glGetUniformLocation(animationProgram, "projection");
  glUniformMatrix4fv(animprojLoc, 1, GL_FALSE,
                     (float *)renderer->camera_matrix);

  renderer->spriteShader = spriteProgram;
  renderer->animationShader = animationProgram;

  // Add this to your Imzi_InitRenderer function after OpenGL context creation
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Imzi_DeinitRenderer(Imzi_Renderer_Ptr renderer) {
  if (renderer->renderContext)
    SDL_GL_DestroyContext(renderer->renderContext);

  Imzi_Deinit(&renderer->ctx);
}

void Imzi_RendererExecuteDrawSprite(Imzi_Renderer_Ptr renderer,
                                    int32_t sprite_index, vec3 translate,
                                    vec3 size) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;
  SpriteSheet *sheet =
      renderer->manager.sprite_sheets + sprite->sprite_sheet_index;

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, translate);
  glm_scale(model, size);

  glBindVertexArray(sprite->vao);
  glUseProgram(renderer->spriteShader);

  GLint modelLoc = glGetUniformLocation(renderer->spriteShader, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sheet->texture.id);

  GLint image = glGetUniformLocation(renderer->spriteShader, "image");
  glUniform1i(image, 0);

  // Set sprite color uniform
  GLint colorLoc = glGetUniformLocation(renderer->spriteShader, "spriteColor");
  glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Imzi_RendererDrawStaticSprite(Imzi_Renderer_Ptr renderer,
                                   int32_t sprite_index, vec2 position) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;

  vec3 translate;
  glm_vec2_copy(position, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy(sprite->size, size);

  Imzi_RendererExecuteDrawSprite(renderer, sprite_index, translate, size);
}

void Imzi_RendererDrawStaticSpriteTo(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_index, SDL_FRect *area) {
  vec3 translate;
  glm_vec2_copy((vec2){area->x, area->y}, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy((vec2){area->w, area->h}, size);

  Imzi_RendererExecuteDrawSprite(renderer, sprite_index, translate, size);
}

void Imzi_RendererDrawSprite(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                             vec2 position) {
  Sprite *sprite = renderer->manager.sprites + sprite_index;

  vec3 translate;
  glm_vec2_sub(position, renderer->render_shift, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy(sprite->size, size);

  Imzi_RendererExecuteDrawSprite(renderer, sprite_index, translate, size);
}

void Imzi_RendererDrawSpriteTo(Imzi_Renderer_Ptr renderer, int32_t sprite_index,
                               SDL_FRect *area) {
  vec3 translate;
  glm_vec2_sub((vec2){area->x, area->y}, renderer->render_shift, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy((vec2){area->w, area->h}, size);
  Imzi_RendererExecuteDrawSprite(renderer, sprite_index, translate, size);
}

void Imzi_RendererExecuteDrawFrame(Imzi_Renderer_Ptr renderer,
                                   int32_t animation_index, uint frame,
                                   vec3 translate, vec3 size) {
  Animation *animation = renderer->manager.animations + animation_index;
  SpriteSheet *sheet =
      renderer->manager.sprite_sheets + animation->sprite_sheet_index;

  glBindVertexArray(animation->vao);
  glUseProgram(renderer->animationShader);

  mat4 model;
  glm_mat4_identity(model);
  glm_translate(model, translate);
  glm_scale(model, size);

  GLint modelLoc = glGetUniformLocation(renderer->animationShader, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sheet->texture.id);
  GLint image = glGetUniformLocation(renderer->animationShader, "image");
  glUniform1i(image, 0);

  // Set sprite color uniform
  GLint colorLoc =
      glGetUniformLocation(renderer->animationShader, "spriteColor");
  glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

  // Calculate UV shift for the current frame
  float uv_shift = (frame % animation->frame_count) * animation->uv_step;
  GLint uvShiftLoc =
      glGetUniformLocation(renderer->animationShader, "uv_shift");
  glUniform1f(uvShiftLoc, uv_shift);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Imzi_RendererDrawAnimationFrame(Imzi_Renderer_Ptr renderer,
                                     int32_t animation_index, uint frame,
                                     vec2 position, SDL_FlipMode mode) {

  Animation *animation = renderer->manager.animations + animation_index;

  vec3 translate;
  glm_vec2_sub(position, renderer->render_shift, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy(animation->size, size);

  // Handle flipping by scaling negatively
  if (mode & SDL_FLIP_HORIZONTAL) {
    translate[0] += animation->size[0];
    size[0] = -size[0];
  }
  if (mode & SDL_FLIP_VERTICAL) {
    translate[1] += animation->size[1];
    size[1] = -size[1];
  }

  Imzi_RendererExecuteDrawFrame(renderer, animation_index, frame, translate,
                                size);
}

void Imzi_RendererDrawAnimationFrameTo(Imzi_Renderer_Ptr renderer,
                                       int32_t animation_index, uint frame,
                                       SDL_FRect *dest, SDL_FlipMode mode) {
  Animation *animation = renderer->manager.animations + animation_index;

  glBindVertexArray(animation->vao);
  glUseProgram(renderer->animationShader);

  vec3 translate;
  glm_vec2_sub((vec2){dest->x, dest->y}, renderer->render_shift, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy((vec2){dest->w, dest->h}, size);

  // Handle flipping by scaling negatively
  if (mode & SDL_FLIP_HORIZONTAL) {
    translate[0] += dest->w;
    size[0] = -size[0];
  }
  if (mode & SDL_FLIP_VERTICAL) {
    translate[1] += dest->h;
    size[1] = -size[1];
  }

  Imzi_RendererExecuteDrawFrame(renderer, animation_index, frame, translate,
                                size);
}

void Imzi_RendererDrawStaticAnimationFrame(Imzi_Renderer_Ptr renderer,
                                           int32_t animation_index, uint frame,
                                           vec2 position, SDL_FlipMode mode) {

  Animation *animation = renderer->manager.animations + animation_index;

  vec3 translate;
  glm_vec2_copy(position, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy(animation->size, size);

  // Handle flipping by scaling negatively
  if (mode & SDL_FLIP_HORIZONTAL) {
    translate[0] += animation->size[0];
    size[0] = -size[0];
  }
  if (mode & SDL_FLIP_VERTICAL) {
    translate[1] += animation->size[1];
    size[1] = -size[1];
  }

  Imzi_RendererExecuteDrawFrame(renderer, animation_index, frame, translate,
                                size);
}

void Imzi_RendererDrawStaticAnimationFrameTo(Imzi_Renderer_Ptr renderer,
                                             int32_t animation_index,
                                             uint frame, SDL_FRect *dest,
                                             SDL_FlipMode mode) {
  Animation *animation = renderer->manager.animations + animation_index;

  glBindVertexArray(animation->vao);
  glUseProgram(renderer->animationShader);

  vec3 translate;
  glm_vec2_copy((vec2){dest->x, dest->y}, translate);
  translate[2] = 0;

  vec3 size;
  glm_vec2_copy((vec2){dest->w, dest->h}, size);

  // Handle flipping by scaling negatively
  if (mode & SDL_FLIP_HORIZONTAL) {
    translate[0] += dest->w;
    size[0] = -size[0];
  }
  if (mode & SDL_FLIP_VERTICAL) {
    translate[1] += dest->h;
    size[1] = -size[1];
  }

  Imzi_RendererExecuteDrawFrame(renderer, animation_index, frame, translate,
                                size);
}

// ======================================================================

int32_t Imzi_RendererLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                     const char *path) {
  return Imzi_AssetManager2DLoadSpriteSheet(&renderer->manager, path);
}

int32_t Imzi_RendererGetSpriteSheet(Imzi_Renderer_Ptr renderer,
                                    const char *path) {
  return Imzi_AssetManager2DGetSpriteSheet(&renderer->manager, path);
}

int32_t Imzi_RendererGetOrLoadSpriteSheet(Imzi_Renderer_Ptr renderer,
                                          const char *path) {
  return Imzi_AssetManager2DGetOrLoadSpriteSheet(&renderer->manager, path);
}

int32_t Imzi_RendererCreateSpriteFromPath(Imzi_Renderer_Ptr renderer,
                                          const char *path, const char *name,
                                          SDL_FRect *area) {
  return Imzi_AssetManager2DCreateSpriteFromPath(&renderer->manager, path, name,
                                                 area);
}

int32_t Imzi_RendererCreateSprite(Imzi_Renderer_Ptr renderer,
                                  int32_t sprite_sheet_index, const char *name,
                                  SDL_FRect *area) {
  return Imzi_AssetManager2DCreateSprite(&renderer->manager, sprite_sheet_index,
                                         name, area);
}

int32_t Imzi_RendererGetSpriteByName(Imzi_Renderer_Ptr renderer,
                                     const char *name) {
  return Imzi_AssetManager2DGetSpriteByName(&renderer->manager, name);
}

int32_t Imzi_RendererCreateAnimationFromPath(Imzi_Renderer_Ptr renderer,
                                             const char *path, const char *name,
                                             SDL_FRect *area, float frame_h,
                                             float frame_w, int32_t frame_count,
                                             double frame_time, bool loop) {
  return Imzi_AssetManager2DCreateAnimationFromPath(
      &renderer->manager, path, name, area, frame_h, frame_w, frame_count,
      frame_time, loop);
}

int32_t Imzi_RendererCreateAnimation(Imzi_Renderer_Ptr renderer,
                                     int32_t sprite_sheet_index,
                                     const char *name, SDL_FRect *area,
                                     float frame_h, float frame_w,
                                     int32_t frame_count, double frame_time,
                                     bool loop) {
  return Imzi_AssetManager2DCreateAnimation(
      &renderer->manager, sprite_sheet_index, name, area, frame_h, frame_w,
      frame_count, frame_time, loop);
}

int32_t Imzi_RendererGetAnimationByName(Imzi_Renderer_Ptr renderer,
                                        const char *name) {
  return Imzi_AssetManager2DGetAnimationByName(&renderer->manager, name);
}
