#include "engine/engine.h"
#include "game/scenes/test_scene.h"
#include "game/scenes/entities/test_entities.h"
#include <SDL3/SDL.h>

Scene* SetupTest1Scene(Imzi_Engine_Ptr engine) {
    Scene *scene = SDL_malloc(sizeof(Scene));

    Entity entity = SetupTestEntity(engine);

    Imzi_AddEntityToScene(scene, entity);

    return scene;
}