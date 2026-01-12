#include "sprite_atlas.h"
#include "core/assets.h"
#include "core/provider.h"
#include "core/path_resolver.h"

#include <pugixml.hpp>

SpriteAtlas::SpriteAtlas(const char* atlas_path)
{
    pugi::xml_document doc;
    std::string real_path = ResolvePath(atlas_path);
    pugi::xml_parse_result result = doc.load_file(real_path.c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to load sprite atlas XML");
    }

    auto tileset = doc.child("tileset");
    m_sprite_size.x = tileset.attribute("tilewidth").as_int();
    m_sprite_size.y = tileset.attribute("tileheight").as_int();

    std::string texture_path = tileset.child("image").attribute("source").as_string();
    m_texture = Provider::Self().Assets()->GetTexture(texture_path);

    auto get_props = [](pugi::xml_node tile, auto& sprite) {
        auto properties = tile.child("properties");
        for (auto property : properties.children("property"))
        {
            std::string name = property.attribute("name").as_string();
            std::string value = property.attribute("value").as_string();
            std::string type = property.attribute("type").as_string();

            sprite.AddProperty(std::move(name), SpriteProperty(type, std::move(value)));
        }
    };

    for (auto tile : tileset.children("tile"))
    {
        int id = tile.attribute("id").as_int();
        std::string type = tile.attribute("type").as_string();

        if (tile.child("animation"))
        {
            std::vector<SpriteAnimationFrameInfo> frames;
            for (auto frame : tile.child("animation").children("frame"))
            {
                int frame_id = frame.attribute("tileid").as_int();
                int duration = frame.attribute("duration").as_int();
                frames.emplace_back(SpriteAnimationFrameInfo{frame_id, duration});
            }

            AnimationSprite anim_sprite(*this, id, std::move(type), std::move(frames));
            get_props(tile, anim_sprite);

            m_animation_sprites.emplace(id, anim_sprite);
        }
        else
        {
            Sprite sprite(*this, id, std::move(type));
            get_props(tile, sprite);

            m_sprites.emplace(id, sprite);
        }
    }
}

const Sprite& SpriteAtlas::GetSpriteById(int id) const
{
    auto it = m_sprites.find(id);
    if (it != m_sprites.end())
    {
        return it->second;
    }

    auto pos = GetSpritePositionInAtlas(id);
    if (pos.x <= (m_texture.Src.w - m_sprite_size.x) &&
        pos.y <= (m_texture.Src.h - m_sprite_size.y))
    {
        // If the sprite ID is valid in terms of position but not found in the map,
        // create a default sprite on-the-fly.
        Sprite sprite(*this, id, "");
        m_sprites.emplace(id, sprite);
        return m_sprites.at(id);
    }

    throw std::runtime_error("Sprite ID not found");
}

const AnimationSprite& SpriteAtlas::GetAnimationSpriteById(int id) const
{
    auto it = m_animation_sprites.find(id);
    if (it != m_animation_sprites.end())
    {
        return it->second;
    }
    throw std::runtime_error("Animation sprite ID not found");
}

Texture SpriteAtlas::GetTextureBySpriteId(int id) const
{
    Point sprite_pos = GetSpritePositionInAtlas(id);
    Texture sprite_texture = m_texture;
    sprite_texture.Src = sprite_texture.Dest = SDL_Rect{sprite_pos.x, sprite_pos.y, m_sprite_size.x, m_sprite_size.y};
    return sprite_texture;
}

Point SpriteAtlas::GetSpritePositionInAtlas(int id) const
{
    int sprites_per_row = m_texture.Src.w / m_sprite_size.x;
    int x = (id % sprites_per_row) * m_sprite_size.x;
    int y = (id / sprites_per_row) * m_sprite_size.y;
    return Point{x, y};
}
