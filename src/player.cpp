#include "player.h"
#include "core/scene.h"
#include "affiliate/spriteAnim.h"

void Player::init()
{
    Actor::init(); // 调用父类的初始化方法
    SpriteAnim* spriteAnim = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.5f, true);
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event); // 调用父类的事件处理方法
}

void Player::update(float dt)
{
    Actor::update(dt); // 调用父类的更新方法

    keyboardControl();
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

void Player::move(float dt)
{
    SDL_Log("Player position: (%f, %f)", position_.x, position_.y);
    setPosition(position_ + velocity_ * dt);
    // 限制玩家在世界边界内
    position_ = glm::clamp(position_, glm::vec2(0.f, 0.f), game_.getCurrentScene()->getWorldSize());
}

void Player::followCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.f);

}
