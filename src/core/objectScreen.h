#pragma once

#include"object.h"

class ObjectScreen : public Object
{

protected:
    glm::vec2 screenPosition_ = glm::vec2(0.f, 0.f);
public:
    ObjectScreen() = default;
    virtual ~ObjectScreen() = default;

    // getter and setter
    const glm::vec2& getScreenPosition() const { return screenPosition_; }
    virtual void setScreenPosition(const glm::vec2& pos) { screenPosition_ = pos; }


};

