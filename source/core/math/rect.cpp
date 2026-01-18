#include "rect.h"

#include <SDL_rect.h>
#include <utility>

Rect Expand(const Rect& rect, const Rect& other)
{
    int x1 = std::min(rect.x, other.x);
    int y1 = std::min(rect.y, other.y);
    int x2 = std::max(rect.x + rect.w, other.x + other.w);
    int y2 = std::max(rect.y + rect.h, other.y + other.h);

    return Rect {
        x1,
        y1,
        x2 - x1,
        y2 - y1,
    };
}
