#pragma once

#include "misc.h"
#include <SDL.h>

using Point = SDL_Point;
using FPoint = SDL_FPoint;

Point operator-(const Point& l, const Point& r);
Point operator+(const Point& l, const Point& r);
Point operator*(const Point& l, int value);
Point RotatedPoint(const Point& center, float angle_rad, const SDL_Point& p);

template <>
inline Point Clamp<Point>(const Point& p, const Point& min, const Point& max)
{
    return { Clamp(p.x, min.x, max.x), Clamp(p.y, min.y, max.y) };
}

inline FPoint operator-(const FPoint& l, const FPoint& r)
{
    return { l.x - r.x, l.y - r.y };
}

inline FPoint operator+(const FPoint& l, const FPoint& r)
{
    return { l.x + r.x, l.y + r.y };
}

inline FPoint operator*(const FPoint& l, float value)
{
    return { l.x * value, l.y * value };
}

inline Point ToPoint(const FPoint& p)
{
    return Point { static_cast<int>(p.x), static_cast<int>(p.y) };
}

inline FPoint ToFPoint(const Point& p)
{
    return FPoint { static_cast<float>(p.x), static_cast<float>(p.y) };
}