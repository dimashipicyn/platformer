#pragma once

#include "core/app.h"

class GameApp : public App
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

private:
};