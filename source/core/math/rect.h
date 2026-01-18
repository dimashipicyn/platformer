#pragma once

#include "point.h"
#include <SDL_rect.h>

using Rect = SDL_Rect;
using FRect = SDL_FRect;

inline bool Contains(const Rect& rect, const Point& point)
{
    return SDL_PointInRect(&point, &rect);
}

inline bool Intersect(const Rect& rect, const Rect& other)
{
    return SDL_HasIntersection(&rect, &other);
}

inline bool Contains(const FRect& rect, const FPoint& point)
{
    return SDL_PointInFRect(&point, &rect);
}

inline bool Intersect(const FRect& rect, const FRect& other)
{
    return SDL_HasIntersectionF(&rect, &other);
}

Rect Expand(const Rect& rect, const Rect& other);

inline Point Center(const Rect& rect)
{
    return { rect.x + rect.w / 2, rect.y + rect.h / 2};
}