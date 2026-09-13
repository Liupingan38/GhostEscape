#pragma once

#include "objectScreen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0.f, 0.f);
    Collider* collider_ = nullptr; // 碰撞体组件指针
public:
    ObjectWorld() = default;
    virtual ~ObjectWorld() = default;
    
    virtual void init() override {type_ = ObjectType::OBJECT_WORLD;}
    virtual void update(float dt) override;

    // getter and setter
    const Collider* getCollider() const { return collider_; }
    void setCollider(Collider* collider) { collider_ = collider; }
    const glm::vec2& getPosition() const override{ return position_; }
    virtual void setPosition(const glm::vec2& pos);
    virtual void setScreenPosition(const glm::vec2& pos) override;

};