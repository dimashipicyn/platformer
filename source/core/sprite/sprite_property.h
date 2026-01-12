#pragma once

#include <string>
#include <variant>

class SpriteProperty
{
public:
    SpriteProperty(const std::string& type, std::string value);

    operator const std::string&() const
    {
        return std::get<std::string>(m_data);
    }

    operator int() const
    {
        return std::get<int>(m_data);
    }

    operator float() const
    {
        return std::get<float>(m_data);
    }

private:
    std::variant<std::string, int, float> m_data;
};