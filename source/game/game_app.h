#pragma once

#include "core/app.h"
#include "core/sprite/map.h"

class GameApp : public App
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

    const Map& GetMap() const
    {
        return m_map;
    }

private:
    Map m_map;
};