#ifndef RENDER_H
#define RENDER_H

#include "engine/managers/asset_manager_2d.h"

void Imzi_RendererDrawSprite(Imzi_Engine_Ptr engine, AssetManager2D *manager,
                             int32_t sprite_index, vec2 position);

#endif
