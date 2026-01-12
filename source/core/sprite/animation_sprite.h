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
    AnimationSprite(const SpriteAtlas& atlas, int id, std::string type, std::vector<SpriteAnimationFrameInfo> frames);

    void Update(float deltatime);
    void Draw(Renderer& r, const Point& pos) const;

private:
    const SpriteAtlas& m_atlas;

    int m_current_frame{};
    int m_current_frame_time_acc{};
    std::vector<SpriteAnimationFrameInfo> m_frames;
};