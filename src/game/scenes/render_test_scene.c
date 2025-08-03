#include "game/scenes/render_test_scene.h"
#include "game/scenes/entities/test_render_entitiy.h"

void SetupRenderTestScene(Imzi_Engine_Ptr engine, Scene *scene) {
  Entity *player_entity = Imzi_AddEntityToScene(scene);
  SetupTestRenderEntity(engine, player_entity);
}
