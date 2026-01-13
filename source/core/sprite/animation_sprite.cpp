#include "animation_sprite.h"

#include "core/texture.h"
#include "sprite_atlas.h"

AnimationSprite::AnimationSprite(const SpriteAtlas& atlas, std::vector<SpriteAnimationFrameInfo> frames)
    : Sprite(), m_atlas(atlas), m_frames(std::move(frames))
{
}

void AnimationSprite::Update(float deltatime)
{
    m_current_frame_time_acc += static_cast<int>(deltatime * 1000);
    int frame_duration = m_frames[m_current_frame].duration;
    if (m_current_frame_time_acc >= frame_duration)
    {
        m_current_frame = (m_current_frame + 1) % m_frames.size();
        m_current_frame_time_acc = 0;
    }
}

void AnimationSprite::Draw(Renderer& r, const Point& pos) const
{
    int id = m_frames[m_current_frame].sprite_id;
    const auto& sprite = m_atlas.GetSpriteById(id);
    sprite.Draw(r, pos);
}
