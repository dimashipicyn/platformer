#pragma once

#include "sprite_atlas.h"

#include <string>
#include <map>

class Map
{
public:
    void Load(const char* map_path);

    void Update(float deltatime);
    void Draw(Renderer& r);

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

    const Sprite& GetSpriteById(size_t id);

    std::vector<Layer> m_layers;
    std::map<size_t, SpriteAtlas::Ptr> m_sprite_atlas_map;
    
    std::vector<Object> m_objs;
};
