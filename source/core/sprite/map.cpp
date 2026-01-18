#include "map.h"

#include "core/path_resolver.h"
#include "core/sprite/animation_sprite.h"
#include "pugixml.hpp"
#include <sstream>
#include <stdexcept>

void Map::Load(const char* map_path)
{
    pugi::xml_document doc;
    std::string real_path = ResolvePath(map_path);
    pugi::xml_parse_result result = doc.load_file(real_path.c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to load sprite atlas XML");
    }

    auto map = doc.child("map");
    for (auto& tileset : map.children("tileset"))
    {
        const int gid = tileset.attribute("firstgid").as_int();
        const char* source = tileset.attribute("source").as_string();

        m_sprite_atlas_map.emplace(gid, std::make_unique<SpriteAtlas>(source));
    }

    for (auto& layer : map.children("layer"))
    {
        const size_t id = layer.attribute("id").as_uint();
        const int width = layer.attribute("width").as_int();
        const int height = layer.attribute("height").as_int();
        const char* data = layer.child_value("data");

        Layer l { id, { width, height }, {} };

        std::stringstream ss { data };
        while (!ss.eof())
        {
            int tile_id {};
            char c;
            ss >> tile_id >> c;
            l.data.push_back(tile_id);
        }

        m_layers.push_back(std::move(l));
    }

    for (auto o : map.child("objectgroup").children("object"))
    {
        auto gid = o.attribute("gid").as_uint();
        auto x = o.attribute("x").as_float();
        auto y = o.attribute("y").as_float();
        // auto width = o.attribute("width").as_float();
        // auto height = o.attribute("height").as_float();

        Object obj{FPoint{x, y}, GetSpriteById(gid).Clone()};
        m_objs.emplace_back(std::move(obj));
    }
}

void Map::Update(float deltatime)
{
    for (auto& o : m_objs)
    {
        o.sprite->Update(deltatime);
    }
}

void Map::Draw(Renderer& r)
{
    for (Layer& l : m_layers) {
        for (size_t i = 0; i < l.data.size(); i++) {
            auto id = l.data[i];
            if (id == 0) {
                continue;
            }

            auto& s = GetSpriteById(id);

            auto size = s.GetSize();
            int x = (i % l.size.x) * size.x;
            int y = (i / l.size.y) * size.y;
            Point offset{x, y};
            s.Draw(r, offset);
        }
    }

    for (auto& o : m_objs)
    {
        Point pos{(int)o.pos.x, (int)o.pos.y};
        o.sprite->Draw(r, pos);
    }
}

const Sprite& Map::GetSpriteById(size_t id)
{
    for (const auto& [gid, atlas] : m_sprite_atlas_map)
    {
        const auto max_gid = gid + atlas->GetSpriteCount();
        if (id >= gid && id < max_gid)
        {
            const auto real_id = id - gid;
            return atlas->GetSpriteById(real_id);
        }
    }

    static Sprite s;
    return s;
}