#include "collider.h"

void Collider::render()
{
    ObjectAffiliate::render(); // 调用父类的渲染方法
#ifdef DEBUG_MODE
    game_.renderFilledCircle(parent_->getScreenPosition() + offset_, size_, 0.3f); // 绘制半透明圆形
#endif //DEBUG_MODE
}

Collider *Collider::addColliderComponent(ObjectScreen *parent, glm::vec2 size, glm::vec2 offset, ColliderType type)
{
    auto collider = new Collider();
    collider->init();
    collider->setParent(parent);
    collider->setSize(size);
    collider->setOffset(offset);
    collider->setColliderType(type);
    parent->addChild(collider);
    return collider;
}

bool Collider::checkCollision(const Collider &other) const
{
    if(!parent_ || !other.parent_) return false; // 如果任一碰撞体没有父对象，返回false
    if(collider_type_ == ColliderType::COLLIDER_CIRCLE && other.collider_type_ == ColliderType::COLLIDER_CIRCLE){
        
        // 圆形碰撞检测
        glm::vec2 this_center = parent_->getPosition() + offset_ + size_ * 0.5f;
        glm::vec2 other_center = other.parent_->getPosition() + other.offset_ + other.size_ * 0.5f;
        float distance = glm::length(this_center - other_center);
        float radius_sum = size_.x * 0.5f + other.size_.x * 0.5f;
        return distance < radius_sum;
    }
    else if(collider_type_ == ColliderType::COLLIDER_RECTANGLE && other.collider_type_ == ColliderType::COLLIDER_RECTANGLE){
        // 矩形碰撞检测(代码还么审)
        glm::vec2 this_pos = parent_->getPosition() + offset_;
        glm::vec2 other_pos = other.parent_->getPosition() + other.offset_;
        return (this_pos.x < other_pos.x + other.size_.x &&
                this_pos.x + size_.x > other_pos.x &&
                this_pos.y < other_pos.y + other.size_.y &&
                this_pos.y + size_.y > other_pos.y);
    }
    return false;
}
