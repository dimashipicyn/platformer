#pragma once

#include "core/renderer.h"
#include "core/texture.h"
#include "sprite_collision.h"
#include "sprite_property.h"

#include <map>

class Sprite
{
public:
    using Ptr = std::unique_ptr<Sprite>;

    Sprite() = default;
    Sprite(Texture texture);
    virtual ~Sprite() = default;

    void AddProperty(std::string name, SpriteProperty property)
    {
        m_props.emplace(std::move(name), std::move(property));
    }

    const SpriteProperty& GetProperty(const std::string& name) const
    {
        return m_props.at(name);
    }

    Size GetSize() const;

    virtual void Update(float /*deltatime*/) { };
    virtual void Draw(Renderer& r, const Point& pos) const;
    virtual Ptr Clone() const
    {
        return std::make_unique<Sprite>(*this);
    }

    void SetCollision(SpriteCollision collision)
    {
        std::swap(m_collision, collision);
    }

private:
    Texture m_texture;
    std::map<std::string, SpriteProperty> m_props;
    SpriteCollision m_collision;
};