#pragma once

#include "sprite.h"
#include "animation_sprite.h"

#include "core/texture.h"

#include <map>

class SpriteAtlas
{
public:
    SpriteAtlas(const char* atlas_path);

    const Sprite& GetSpriteById(int id) const;
    const AnimationSprite& GetAnimationSpriteById(int id) const;

    Texture GetTextureBySpriteId(int id) const;
private:
    Point GetSpritePositionInAtlas(int id) const;
    
    Size m_sprite_size;
    Texture m_texture;
    mutable std::map<int, Sprite> m_sprites;
    std::map<int, AnimationSprite> m_animation_sprites;
};