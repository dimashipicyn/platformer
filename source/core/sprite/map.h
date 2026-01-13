#pragma once

#include "sprite_atlas.h"

#include <string>
#include <map>

class Map
{
public:
    void Load(const char* map_path);

private:
    struct Layer {
        int id{};
        Size size{};
        std::vector<int> data;
    };

    Sprite GetSpriteById(int id);

    std::vector<Layer> m_layers;
    std::map<int, SpriteAtlas> m_sprite_atlas_map;
};












struct Tile {};

struct Tileset {
    Tile tiles[32];
    int gid = 0;
    int count = 32;
};

Tileset tilesets[2];

Tile get_tile(int id) {
    for (Tileset t : tilesets) {
        if (t.gid >= id && id < (t.gid + t.count)) {
            return t.tiles[id - t.gid];
        }
    }
};