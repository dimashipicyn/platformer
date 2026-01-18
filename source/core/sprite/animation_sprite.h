#pragma once

#include "sprite.h"

class SpriteAtlas;

struct SpriteAnimationFrameInfo {
    int sprite_id{};
    int duration{};
};

class AnimationSprite : public Sprite
{
public:
    using Ptr = std::unique_ptr<AnimationSprite>;

    AnimationSprite(Texture texture, const SpriteAtlas& atlas, std::vector<SpriteAnimationFrameInfo> frames);

    void Update(float deltatime) override;
    void Draw(Renderer& r, const Point& pos) const override;
    
    Sprite::Ptr Clone() const override
    {
        return std::make_unique<AnimationSprite>(*this);
    }
    
private:
    const SpriteAtlas& m_atlas;

    int m_current_frame{};
    int m_current_frame_time_acc{};
    std::vector<SpriteAnimationFrameInfo> m_frames;
};