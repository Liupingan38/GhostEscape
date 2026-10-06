#pragma once

#include "core/actor.h"
#include "affiliate/spriteAnim.h"
#include "world/effect.h"

class Player : public Actor
{
private:
    SpriteAnim *sprite_idle_ = nullptr;
    SpriteAnim *sprite_move_ = nullptr;
    Effect* death_effect_ = nullptr;
    bool is_moving_ = false; // 玩家是否在移动
public:
    Player() = default;
    virtual ~Player() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    
    void keyboardControl(); // 玩家控制相关
    void followCamera(); // 相机跟随
    void checkState(); // 检查角色状态
    void changeState(bool isMoving); // 改变角色状态
    void checkIsAlive(); //检查角色是否存活
    
};