#pragma once

#include "../core/objectAffiliate.h"

class Collider: public ObjectAffiliate
{
private:
    enum class ColliderType
    {
        COLLIDER_RECTANGLE,
        COLLIDER_CIRCLE
    };
    ColliderType collider_type_;

public:
    virtual void render() override;

    static Collider* addColliderComponent(ObjectScreen* parent, glm::vec2 size, 
        glm::vec2 offset = glm::vec2(0.f, 0.f), ColliderType type = ColliderType::COLLIDER_CIRCLE);
    
    bool checkCollision(const Collider& other) const;

	//setters and getters
    ColliderType getColliderType() const { return collider_type_; }
    void setColliderType(ColliderType type) { collider_type_ = type; }

};