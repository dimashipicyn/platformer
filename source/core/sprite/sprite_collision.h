#pragma once

#include "core/math/rect.h"

#include <algorithm>
#include <vector>

class SpriteCollision
{
public:
    SpriteCollision() = default;
    SpriteCollision(const FRect& rect)
        : m_rects { rect }
    {
    }

    void AddRect(const FRect& rect)
    {
        m_rects.push_back(rect);
    }

    bool Intersects(const FPoint& cur_pos, const SpriteCollision& other, const FPoint& other_pos) const
    {
        return std::any_of(m_rects.begin(), m_rects.end(), [&](const FRect& rect)
            {
                FRect real_cur{rect.x + cur_pos.x, rect.y + cur_pos.y, rect.w, rect.h};
                return other.Intersects(other_pos, real_cur);
            });
    }

    bool Intersects(const FPoint& cur_pos, const FRect& other) const
    {
        return std::any_of(m_rects.begin(), m_rects.end(), [&](const FRect& rect)
            {
                FRect real_cur{rect.x + cur_pos.x, rect.y + cur_pos.y, rect.w, rect.h};
                return Intersect(real_cur, other);
            });
    }

private:
    std::vector<FRect> m_rects;
};