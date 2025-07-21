#include "engine/managers/asset_manager_2d.h"

AssetManager2D *Imzi_CreateAssetManager2D()
{
    AssetManager2D *manager = SDL_malloc(sizeof(AssetManager2D));

    manager->sprite_sheet_count = 0;
    manager->sprite_count = 0;
    manager->animation_count = 0;

    return manager;
}

void Imzi_DestroyAssetManager2D(AssetManager2D *manager)
{
    SDL_free(manager);
}

int32_t Imzi_AssetManager2DLoadSpriteSheet(Imzi_Engine_Ptr engine, AssetManager2D *manager, const char *path)
{
    if (manager->sprite_sheet_count == MAX_ASSET_COUNT)
    {
        return -1;
    }

    SpriteSheet *sprite_sheet = Imzi_LoadSpriteSheet(engine, path);
    assert(sprite_sheet != NULL);

    SDL_strlcpy(sprite_sheet->name, path, 64);
    manager->sprite_sheets[manager->sprite_sheet_count++] = sprite_sheet;
    assert(manager->sprite_sheets[manager->sprite_sheet_count - 1] != NULL);

    return manager->sprite_sheet_count - 1;
}

int32_t Imzi_AssetManager2DGetSpriteSheet(AssetManager2D *manager, const char *path)
{
    for (int32_t i = 0; i < manager->sprite_sheet_count; i++)
    {
        SpriteSheet *sprite_sheet = manager->sprite_sheets[i];
        if (SDL_strcmp(sprite_sheet->name, path) == 0)
        {
            return i;
        }
    }

    return -1;
}

int32_t Imzi_AssetManager2DGetOrLoadSpriteSheet(Imzi_Engine_Ptr engine, AssetManager2D *manager, const char *path)
{
    int32_t sheet_index = Imzi_AssetManager2DGetSpriteSheet(manager, path);

    if (sheet_index == -1)
    {
        sheet_index = Imzi_AssetManager2DLoadSpriteSheet(engine, manager, path);
    }

    assert(sheet_index != -1);

    return sheet_index;
}

int32_t Imzi_AssetManager2DCreateSprite(AssetManager2D *manager, int32_t sprite_sheet_index, const char *name, SDL_FRect *area)
{
    if (manager->sprite_count == MAX_ASSET_COUNT)
    {
        return -1;
    }

    Sprite *sprite = (Sprite *)SDL_malloc(sizeof(Sprite));
    sprite->sprite_sheet_index = sprite_sheet_index;
    SDL_strlcpy(sprite->name, name, 64);

    if (area == NULL)
    {
        SpriteSheet *sheet = manager->sprite_sheets[sprite_sheet_index];
        sprite->area = (SDL_FRect){0, 0, sheet->texture->w, sheet->texture->h};
    }
    else
    {
        sprite->area = *area;
    }

    manager->sprites[manager->sprite_count++] = sprite;

    return manager->sprite_count - 1;
}

int32_t Imzi_AssetManager2DCreateSpriteFromPath(Imzi_Engine_Ptr engine, AssetManager2D *manager, const char *path, const char *name, SDL_FRect *area)
{
    int32_t sprite_sheet_index = Imzi_AssetManager2DGetOrLoadSpriteSheet(engine, manager, path);

    if (sprite_sheet_index == -1)
    {
        return -1;
    }

    return Imzi_AssetManager2DCreateSprite(manager, sprite_sheet_index, name, area);
}

int32_t Imzi_AssetManager2DCreateAnimation(AssetManager2D *manager, int32_t sprite_sheet_index, const char *name, SDL_FRect *area, float frame_h, float frame_w, int32_t frame_count, double frame_time, bool loop)
{
    if (manager->animation_count == MAX_ASSET_COUNT)
    {
        return -1;
    }

    assert((frame_w * frame_count) >= area->w);
    assert(frame_h >= area->h);

    Animation *animation = (Animation *)SDL_malloc(sizeof(Animation));
    animation->sprite_sheet_index = sprite_sheet_index;
    animation->frame_h = frame_h;
    animation->frame_w = frame_w;
    animation->frame_time = frame_time;
    animation->frame_count = frame_count;
    animation->loop = loop;

    if (area == NULL)
    {
        SpriteSheet *sheet = manager->sprite_sheets[sprite_sheet_index];
        animation->area = (SDL_FRect){0, 0, sheet->texture->w, sheet->texture->h};
    }
    else
    {
        animation->area = *area;
    }

    SDL_strlcpy(animation->name, name, 64);
    manager->animations[manager->animation_count++] = animation;

    return manager->animation_count - 1;
}

int32_t Imzi_AssetManager2DCreateAnimationFromPath(Imzi_Engine_Ptr engine, AssetManager2D *manager, const char *path, const char *name, SDL_FRect *area, float frame_h, float frame_w, int32_t frame_count, double frame_time, bool loop)
{
    int32_t sprite_sheet_index = Imzi_AssetManager2DGetOrLoadSpriteSheet(engine, manager, path);
    if (sprite_sheet_index == -1)
    {
        return -1;
    }

    return Imzi_AssetManager2DCreateAnimation(manager, sprite_sheet_index, name, area, frame_h, frame_w, frame_count, frame_time, loop);
}

int32_t Imzi_AssetManager2DGetSpriteByName(AssetManager2D *manager, const char *name)
{
    for (int32_t i = 0; i < manager->sprite_count; i++)
    {
        Sprite *sprite = manager->sprites[i];
        if (SDL_strcmp(sprite->name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int32_t Imzi_AssetManager2DGetAnimationByName(AssetManager2D *manager, const char *name)
{
    for (int32_t i = 0; i < manager->animation_count; i++)
    {
        Animation *animation = manager->animations[i];

        if (SDL_strcmp(animation->name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}


void Imzi_RenderSprite(Imzi_Engine_Ptr engine, AssetManager2D *manager, int32_t sprite_index, vec2 position)
{
    Sprite *sprite = manager->sprites[sprite_index];
    SpriteSheet *sheet = manager->sprite_sheets[sprite->sprite_sheet_index];

    SDL_FRect src = {sprite->area.x, sprite->area.y, sprite->area.w, sprite->area.h};
    SDL_FRect dest = {position[0], position[1], sprite->area.w, sprite->area.h};

    Imzi_RenderPartialSpriteSheet(engine, sheet, &src, &dest);
}
