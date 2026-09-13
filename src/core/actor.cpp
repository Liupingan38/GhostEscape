#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"

void Actor::move(float dt)
{
    // SDL_Log("Actor position: (%f, %f)", position_.x, position_.y);
    setPosition(position_ + velocity_ * dt);
    // 限制玩家在世界边界内
    position_ = glm::clamp(position_, glm::vec2(0.f, 0.f), game_.getCurrentScene()->getWorldSize());
}