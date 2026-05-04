#pragma once

#include "core/scene.h"

class Player;

class SceneMain : public Scene
{

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    //getter and setter
    


private:
    // 背景网格参数

    float gridWidth_ = 100.f;
    float borderWidth_ = 10.f;
    SDL_FColor gridColor_ = {0.5f, 0.5f, 0.5f, 1.f};

    void renderBackground();

    //玩家
    Player* player_ = nullptr;
};

