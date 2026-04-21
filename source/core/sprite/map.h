#pragma once

#include "core/math/point.h"
#include "core/sprite/sprite_collision.h"
#include "sprite_atlas.h"

#include <string>
#include <map>

class Map
{
public:
    void Load(const char* map_path);

    void Update(float deltatime);
    void Draw(Renderer& r);

    bool Intersects(const FPoint& pos, const SpriteCollision& sc) const {
        bool intersected = false;
        TilesVisitor([&](const Point& offset, const Sprite& s){
            intersected = sc.Intersects(pos, s.GetCollision(), ToFPoint(offset));
            return !intersected;
        });
        return intersected;
    }

private:
    struct Layer {
        size_t id{};
        Size size{};
        std::vector<int> data;
    };

    struct Object {
        FPoint pos;
        std::unique_ptr<Sprite> sprite;
    };

    template <typename Visitor>
    void TilesVisitor(Visitor&& v) const
    {
        for (const Layer& l : m_layers)
        {
            for (size_t i = 0; i < l.data.size(); i++)
            {
                auto id = l.data[i];
                if (id == 0)
                {
                    continue;
                }

                auto& s = GetSpriteById(id);

                auto size = s.GetSize();
                int x = (i % l.size.x) * size.x;
                int y = (i / l.size.y) * size.y;

                if (!v(Point { x, y }, s))
                    return;
            }
        }
    }

    const Sprite& GetSpriteById(size_t id) const;

    std::vector<Layer> m_layers;
    std::map<size_t, SpriteAtlas::Ptr> m_sprite_atlas_map;
    
    std::vector<Object> m_objs;
};
