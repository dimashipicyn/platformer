#pragma once

#include "core/renderer.h"
#include "sprite_property.h"

#include <map>

class SpriteAtlas;

class Sprite
{
public:
    Sprite(const SpriteAtlas& atlas, int id, std::string type);

    const std::string& GetType() const
    {
        return m_type;
    }
    
    void AddProperty(std::string name, SpriteProperty property)
    {
        m_props.emplace(std::move(name), std::move(property));
    }

    const SpriteProperty& GetProperty(const std::string& name) const
    {
        return m_props.at(name);
    }

    virtual void Update(float /*deltatime*/) {};
    virtual void Draw(Renderer& r, const Point& pos) const;

private:
    const SpriteAtlas& m_atlas;

    int m_id {};
    std::string m_type;
    std::map<std::string, SpriteProperty> m_props;
};