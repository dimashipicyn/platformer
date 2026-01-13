#pragma once

#include "animation_sprite.h"
#include "sprite.h"

#include "core/texture.h"

#include <map>

class SpriteAtlas
{
public:
    SpriteAtlas(const char* atlas_path);

    const Sprite& GetSpriteById(int id) const;
    const AnimationSprite& GetAnimationSpriteById(int id) const;

    size_t GetSpriteCount() const
    {
        return m_count;
    }

    const Size& GetSpriteSize() const
    {
        return m_sprite_size;
    }

private:
    Texture GetTextureBySpriteId(int id) const;
    Point GetSpritePositionInAtlas(int id) const;

    Size m_sprite_size;
    size_t m_count;
    size_t m_columns;
    Texture m_texture;
    mutable std::map<int, Sprite> m_sprites;
    std::map<int, AnimationSprite> m_animation_sprites;
};