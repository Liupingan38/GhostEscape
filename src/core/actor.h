#pragma once

#include "objectWorld.h"
#include<AccCtrl.h>

class Actor : public ObjectWorld
{   
protected:
    glm::vec2 velocity_ = glm::vec2(0.f, 0.f);
    float maxSpeed_ = 500.f; // 每秒最大移动速度
public:
    Actor() = default;
    virtual ~Actor() = default;

    // getter and setter
    const glm::vec2& getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& vel) { velocity_ = vel; }
    float getMaxSpeed() const { return maxSpeed_; }
    void setMaxSpeed(float speed) { maxSpeed_ = speed; }

};