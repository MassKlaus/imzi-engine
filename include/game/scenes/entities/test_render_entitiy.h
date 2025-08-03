#include "engine/engine.h"
#include "engine/entity.h"

typedef struct {
  uint32_t spriteTarget;
} TestRenderEntity;

void SetupTestRenderEntity(Imzi_Engine_Ptr engine, Entity *entity);
