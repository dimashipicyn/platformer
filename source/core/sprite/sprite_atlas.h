#pragma once

#include "sprite.h"
#include "animation_sprite.h"

#include <map>

class SpriteAtlas
{
public:
    SpriteAtlas(const char* atlas_path);

    const Sprite& GetSpriteByType(const char* type) const;
    const Sprite& GetSpriteById(int id) const;

    const AnimationSprite& GetAnimationSpriteByType(const char* type) const;
    const AnimationSprite& GetAnimationSpriteById(int id) const;

    Texture GetTextureBySpriteId(int id) const;
private:
    std::map<int, Sprite> m_sprites;
    std::map<int, AnimationSprite> m_animation_sprites;
};