#include "player.h"
#include "core/scene.h"
#include "affiliate/spriteAnim.h"
#include "raw/stats.h"

void Player::init()
{
    Actor::init(); // 调用父类的初始化方法
    sprite_idle_ = SpriteAnim::addSpriteAnimComponent(this, "assets/sprite/ghost-idle.png", 2.5f);
    sprite_move_ = SpriteAnim::addSpriteAnimComponent(this, "assets/sprite/ghost-move.png", 2.5f);
    sprite_move_->setActive(false); 

    //设置碰撞体
    collider_ = Collider::addColliderComponent(this, sprite_move_->getSize(), 0.8f);

    //设置属性
    stats_ = Stats::addStatsComponent(this);

    //设置死亡特效
    death_effect_ = Effect::addEffectChild(nullptr,"assets/effect/1764.png",nullptr,glm::vec2(0.f, 0.f));

}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event); // 调用父类的事件处理方法
}

void Player::update(float dt)
{
    Actor::update(dt); // 调用父类的更新方法

    keyboardControl();
    checkState();
    checkIsAlive();
    move(dt);
    followCamera();
}

void Player::render()
{
    Actor::render(); // 调用父类的渲染方法

    //game_.drawRect(screenPosition_, screenPosition_ + glm::vec2(50.f, 50.f), 5.f, SDL_FColor{1.f, 0.f, 0.f, 1.f});
}

void Player::clean()
{
    Actor::clean(); // 调用父类的清理方法
}

void Player::keyboardControl()
{
    auto keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_W]) 
    {
        velocity_.y = -maxSpeed_;
    }else if(keyboardState[SDL_SCANCODE_S])
    {
        velocity_.y = maxSpeed_;
    }else if(keyboardState[SDL_SCANCODE_A])
    {
        velocity_.x = -maxSpeed_;
    }else if(keyboardState[SDL_SCANCODE_D])
    {
        velocity_.x = maxSpeed_;
    }else{
        velocity_ *= 0.9f; // 没有按键时逐渐减速  
    }
}

void Player::followCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.f);

}

void Player::checkState()
{
    bool isFlip = velocity_.x < 0.f; // 根据水平速度判断是否翻转
    sprite_idle_->setFlip(isFlip);
    sprite_move_->setFlip(isFlip);

    bool isMovingNow = glm::length(velocity_) > 0.1f; // 判断是否在移动
    
    if(isMovingNow != is_moving_)
    {
        is_moving_ = isMovingNow;
        changeState(is_moving_);
    }
}

void Player::changeState(bool isMoving)
{
    if(isMoving)
    {
        // move 
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurFrame(sprite_idle_->getCurFrame()); // 保持动画帧同步
        sprite_move_->setTimeCounter(sprite_idle_->getTimeCounter()); // 保持动画时间计数器同步
    }else{
        // idle
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurFrame(sprite_move_->getCurFrame());
        sprite_idle_->setTimeCounter(sprite_move_->getTimeCounter());
    }
}

void Player::checkIsAlive()
{
    if(!stats_->getIsAlive()){
        game_.getCurrentScene()->addChildSafe(death_effect_);
        death_effect_->setPosition(getPosition());
        setActive(false);
        
    }
}
