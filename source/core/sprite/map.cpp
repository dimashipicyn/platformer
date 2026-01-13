#include "map.h"

#include "core/path_resolver.h"
#include "pugixml.hpp"
#include <sstream>

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
    for (auto& tileset : map.children("tileset")) {
        const int gid = tileset.attribute("firstgid").as_int();
        const char* source = tileset.attribute("source").as_string();

        m_sprite_atlas_map.emplace(gid, SpriteAtlas{source});
    }

    for (auto& layer : map.child("layer"))
    {
        const int id = layer.attribute("id").as_int();
        const int width = layer.attribute("width").as_int();
        const int height = layer.attribute("height").as_int();
        const char* data = layer.child("data").value();

        Layer l{id, {width, height}, {}};

        std::stringstream ss{data};
        while (!ss.eof()) {
            int tile_id{};
            char c;
            ss >> tile_id >> c;
            l.data.push_back(tile_id);
        }

        m_layers.push_back(std::move(l));
    }
}

const Sprite& Map::GetSpriteById(int id)
{
    for (auto& pair)
}