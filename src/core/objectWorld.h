#pragma once

#include "objectScreen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0.f, 0.f);
public:
    ObjectWorld() = default;
    virtual ~ObjectWorld() = default;
    
    virtual void update(float dt) override;

    // getter and setter
    const glm::vec2& getPosition() const { return position_; }
    virtual void setPosition(const glm::vec2& pos);
    virtual void setScreenPosition(const glm::vec2& pos) override;

};