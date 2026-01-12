#include "sprite.h"

#include "core/texture.h"
#include "sprite_atlas.h"

Sprite::Sprite(const SpriteAtlas& atlas, int id, std::string type)
    : m_atlas(atlas), m_id(id), m_type(std::move(type))
{
}

void Sprite::Draw(Renderer& r, const Point& pos) const
{
    auto tex = m_atlas.GetTextureBySpriteId(m_id);
    r.DrawTexture(tex, pos);
}