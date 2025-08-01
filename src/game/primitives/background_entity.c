#include "game/primitives/background_entity.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/entity.h"
#include <stdint.h>

void RenderBackgroundEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)frame_time;
  BackgroundEntity *entity_data = (BackgroundEntity *)entity->data;
  Imzi_RendererDrawSpriteTo(&engine->renderer, entity_data->sprite_index,
                            &(SDL_FRect){0.0, 0.0, engine->renderer.ctx.width,
                                         engine->renderer.ctx.height});
}

void UpdateBackgroundEntity(Imzi_Engine_Ptr engine, Entity *entity,
                            double frame_time) {
  (void)frame_time;
  (void)entity;
  (void)engine;
}

void SetupBackgroundEntity(int32_t sprite_index, Entity *entity) {
  BackgroundEntity *background_entity = SDL_malloc(sizeof(BackgroundEntity));
  SDL_memset(background_entity, 0, sizeof(BackgroundEntity));
  background_entity->sprite_index = sprite_index;

  entity->data = background_entity;
  entity->renderPtr = RenderBackgroundEntity;
  entity->updatePtr = UpdateBackgroundEntity;
  entity->render_layer = -1;
}
