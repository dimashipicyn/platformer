#include "animation_sprite.h"

#include "core/texture.h"
#include "sprite_atlas.h"

void AnimationSprite::Update(float deltatime)
{

}

void AnimationSprite::Draw(Renderer& r, const Point& pos) const
{
    int id = m_frames[m_current_frame].sprite_id;
    auto tex = m_atlas.GetTextureBySpriteId(id);

    r.DrawTexture(tex, pos);
}
