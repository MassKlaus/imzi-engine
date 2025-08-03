#include "SDL3/SDL_rect.h"
#include "engine/engine.h"
#include "engine/renderer.h"
#include "game/scenes/entities/test_render_entitiy.h"
#include "glad/glad.h"

void RenderTestRenderEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frametime) {
  (void)entity;
  (void)frametime;
  (void)engine;

  TestRenderEntity *data = (TestRenderEntity *)entity->data;

  static float walk_speed = 100.0;
  static float x = 0.0;

  x += walk_speed * frametime;
  Imzi_RendererDrawSprite(&engine->renderer, data->spriteTarget,
                          (vec2){x, 0.0});
}

void UpdateTestRenderEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frametime) {
  (void)engine;
  (void)entity;
  (void)frametime;
}

void SetupTestRenderEntity(Imzi_Engine_Ptr engine, Entity *entity) {
  (void)engine;
  TestRenderEntity *data =
      (TestRenderEntity *)SDL_malloc(sizeof(TestRenderEntity));
  SDL_zero(*data);
  data->spriteTarget = Imzi_RendererCreateSpriteFromPath(
      &engine->renderer, "assets/prejectile.png", "proj",
      &(SDL_FRect){0, 0, 32, 32});

  entity->data = data;
  entity->renderPtr = RenderTestRenderEntity;
  entity->updatePtr = UpdateTestRenderEntity;
  entity->render_layer = 0;
}
