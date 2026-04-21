#pragma once

#include "core/math/point.h"
#include "core/sprite/sprite.h"

class GameApp;

class Player
{
public:
    Player();

    void Update(GameApp& app);
    void Draw(GameApp& app);

private:
    Sprite::Ptr m_sprite{};
    FPoint m_pos{};
    float m_speed{};
};