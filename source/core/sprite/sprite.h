#pragma once

#include "core/renderer.h"
#include "core/texture.h"
#include "sprite_property.h"

#include <map>

class SpriteAtlas;

class Sprite
{
public:
    Sprite() = default;
    Sprite(Texture texture);
    
    void AddProperty(std::string name, SpriteProperty property)
    {
        m_props.emplace(std::move(name), std::move(property));
    }

    const SpriteProperty& GetProperty(const std::string& name) const
    {
        return m_props.at(name);
    }

    Size GetSize() const;

    virtual void Update(float /*deltatime*/) {};
    virtual void Draw(Renderer& r, const Point& pos) const;

private:
    Texture m_texture;
    std::map<std::string, SpriteProperty> m_props;
};