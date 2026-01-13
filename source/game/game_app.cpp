#include "game_app.h"

#include "constant.h"
#include "core/renderer.h"
#include "core/sprite/sprite.h"

void GameApp::OnInit()
{
    // m_sprite_atlas = new SpriteAtlas("main-tileset.tsx");
    // m_pacman = new AnimationSprite{m_sprite_atlas->GetAnimationSpriteById(0)};
    // m_score = new Sprite{m_sprite_atlas->GetSpriteById(8)};

    m_map.Load("map.tmx");
}

void GameApp::OnUpdate()
{
    // m_pacman->Update(DeltaTime);
    m_map.Update(DeltaTime);
}

void GameApp::OnRender()
{
    // m_pacman->Draw(*Renderer, {});
    // m_score->Draw(*Renderer, {24,24});

    m_map.Draw(*Renderer);
}