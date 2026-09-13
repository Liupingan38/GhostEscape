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

    static Collider* addColliderComponent(
        ObjectScreen* parent, 
        glm::vec2 size, 
        float scale =  1.f ,
        ColliderType type = ColliderType::COLLIDER_CIRCLE,
        AnchorType anchor = AnchorType::ANCHOR_CENTER);
    
    bool checkCollision(const Collider& other) const;

	//setters and getters
    ColliderType getColliderType() const { return collider_type_; }
    void setColliderType(ColliderType type) { collider_type_ = type; }

};