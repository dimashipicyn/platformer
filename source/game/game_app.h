#pragma once

#include "core/app.h"
#include "core/sprite/animation_sprite.h"
#include "core/sprite/sprite.h"
#include "core/sprite/sprite_atlas.h"
#include "core/sprite/map.h"

class GameApp : public App
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

private:
    // SpriteAtlas* m_sprite_atlas{};
    // AnimationSprite* m_pacman{};
    // Sprite* m_score{};

    Map m_map;
};