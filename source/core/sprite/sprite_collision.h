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

    bool Intersects(const SpriteCollision& other) const
    {
        return std::any_of(m_rects.begin(), m_rects.end(), [&](const FRect& rect)
            { return other.Intersects(rect); });
    }

    bool Intersects(const FRect& other) const
    {
        return std::any_of(m_rects.begin(), m_rects.end(), [&](const FRect& rect)
            { return Intersect(rect, other); });
    }

private:
    std::vector<FRect> m_rects;
};