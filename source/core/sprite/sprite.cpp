#include "sprite.h"

#include "core/texture.h"
#include "sprite_atlas.h"

void Sprite::Draw(Renderer& r, const Point& pos) const
{
    auto tex = m_atlas.GetTextureBySpriteId(m_id);
    r.DrawTexture(tex, pos);
}