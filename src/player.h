#pragma once

#include "core/actor.h"
#include "affiliate/spriteAnim.h"

class Player : public Actor
{
private:
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    bool is_moving_ = false; // 玩家是否在移动
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

    // 检查角色状态
    void checkState();

    // 改变角色状态
    void changeState(bool isMoving);
};