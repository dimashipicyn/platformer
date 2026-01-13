#include "sprite.h"

#include "core/texture.h"
#include "sprite_atlas.h"

Sprite::Sprite(Texture texture)
    : m_texture(std::move(texture))
{
}

Size Sprite::GetSize() const
{
    return {m_texture.Src.w, m_texture.Src.h};
}

void Sprite::Draw(Renderer& r, const Point& pos) const
{
    r.DrawTexture(m_texture, pos);
}