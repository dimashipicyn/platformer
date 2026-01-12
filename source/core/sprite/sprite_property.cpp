#include "sprite_property.h"

SpriteProperty::SpriteProperty(const std::string& type, std::string value)
    : m_data()
{
    if (type == "string")
    {
        m_data = value;
    }
    else if (type == "int")
    {
        m_data = std::stoi(value);
    }
    else if (type == "float")
    {
        m_data = std::stof(value);
    }
}