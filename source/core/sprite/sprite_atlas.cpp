#include "sprite_atlas.h"
#include "animation_sprite.h"
#include "core/assets.h"
#include "core/path_resolver.h"
#include "core/provider.h"
#include "sprite_collision.h"


#include <memory>
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
    m_count = tileset.attribute("tilecount").as_int();
    m_columns = tileset.attribute("columns").as_int();

    std::string texture_path = tileset.child("image").attribute("source").as_string();
    m_texture = Provider::Self().Assets()->GetTexture(texture_path);

    auto get_props = [](pugi::xml_node tile, auto& sprite)
    {
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

        Sprite::Ptr sprite;
        if (tile.child("animation"))
        {
            std::vector<SpriteAnimationFrameInfo> frames;
            for (auto frame : tile.child("animation").children("frame"))
            {
                int frame_id = frame.attribute("tileid").as_int();
                int duration = frame.attribute("duration").as_int();
                frames.emplace_back(SpriteAnimationFrameInfo { frame_id, duration });
            }

            sprite = std::make_unique<AnimationSprite>(GetTextureBySpriteId(id), *this, std::move(frames));
        }
        else
        {
            sprite = std::make_unique<Sprite>(GetTextureBySpriteId(id));
        }

        SpriteCollision sc;
        
        auto obj_group = tile.child("objectgroup");
        for (auto object : obj_group.children("object"))
        {
            FRect r; 
            r.x = object.attribute("x").as_float();
            r.y = object.attribute("y").as_float();
            r.w = object.attribute("width").as_float();
            r.h = object.attribute("height").as_float();
            sc.AddRect(r);
        }

        sprite->SetCollision(sc);

        get_props(tile, *sprite);
        m_sprites.emplace(id, std::move(sprite));
    }
}

const Sprite& SpriteAtlas::GetSpriteById(int id) const
{
    auto it = m_sprites.find(id);
    if (it != m_sprites.end())
    {
        return *it->second;
    }

    auto pos = GetSpritePositionInAtlas(id);
    if (pos.x <= (m_texture.Src.w - m_sprite_size.x) && pos.y <= (m_texture.Src.h - m_sprite_size.y))
    {
        m_sprites.emplace(id, std::make_unique<Sprite>(GetTextureBySpriteId(id)));
        return *m_sprites.at(id);
    }

    throw std::runtime_error("Sprite ID not found");
}

Texture SpriteAtlas::GetTextureBySpriteId(int id) const
{
    Point sprite_pos = GetSpritePositionInAtlas(id);
    Texture sprite_texture = m_texture;
    sprite_texture.Src = sprite_texture.Dest = SDL_Rect { sprite_pos.x, sprite_pos.y, m_sprite_size.x, m_sprite_size.y };
    return sprite_texture;
}

Point SpriteAtlas::GetSpritePositionInAtlas(int id) const
{
    int x = (id % m_columns) * m_sprite_size.x;
    int y = (id / m_columns) * m_sprite_size.y;
    return Point { x, y };
}
