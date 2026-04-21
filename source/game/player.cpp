#include "player.h"

#include "core/math/point.h"
#include "core/sprite/map.h"
#include "game_app.h"
#include <SDL_scancode.h>

Player::Player()
{
}

void Player::Update(GameApp& app)
{
    const Map& map = app.GetMap();

    FPoint direction { 0, 0 };

    if (app.Input->IsKeyDown(SDL_SCANCODE_W))
        direction.y = -1;
    if (app.Input->IsKeyDown(SDL_SCANCODE_S))
        direction.y = 1;
    if (app.Input->IsKeyDown(SDL_SCANCODE_A))
        direction.x = -1;
    if (app.Input->IsKeyDown(SDL_SCANCODE_D))
        direction.x = 1;

    const auto new_pos = m_pos + (direction * m_speed * app.DeltaTime);
    if (!map.Intersects(new_pos, m_sprite->GetCollision()))
    {
        m_pos = new_pos;
    }
}

void Player::Draw(GameApp& app)
{
    m_sprite->Draw(*app.Renderer, ToPoint(m_pos));
}
