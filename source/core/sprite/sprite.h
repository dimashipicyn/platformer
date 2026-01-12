#pragma once

#include "core/renderer.h"
#include "sprite_property.h"

#include <map>

class SpriteAtlas;

class Sprite
{
public:
    Sprite(int id);

    const std::string& GetType() const
    {
        return m_type;
    }
    
    const SpriteProperty& GetProperty(const std::string& name) const
    {
        return m_props.at(name);
    }

    void Draw(Renderer& r, const Point& pos) const;

private:
    const SpriteAtlas& m_atlas;

    int m_id {};
    std::string m_type;
    std::map<std::string, SpriteProperty> m_props;
};