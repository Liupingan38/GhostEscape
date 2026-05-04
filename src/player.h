#pragma once

#include "core/actor.h"

class Player : public Actor
{
public:
    Player() = default;
    virtual ~Player() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    // 玩家控制相关
    void keyboardControl();
    void move(float dt);

    // 相机跟随
    void followCamera();
};