#include "enemy.h"
#include "core/scene.h"
#include "affiliate/collider.h"

void Enemy::init()
{
    Actor::init(); 

    sprite_move_ = SpriteAnim::addSpriteAnimComponent(this, "assets/sprite/ghost-Sheet.png", 2.5f, true);
    sprite_move_->setActive(true);
    
    sprite_hurt_ = SpriteAnim::addSpriteAnimComponent(this, "assets/sprite/ghostHurt-Sheet.png", 2.5f, true);
    sprite_hurt_->setActive(false);

    sprite_dead_ = SpriteAnim::addSpriteAnimComponent(this, "assets/sprite/ghostDead-Sheet.png", 2.5f, true);
    sprite_dead_->setActive(false);
    sprite_dead_->setLoop(false); // 死亡动画不循环播放

    //设置碰撞体
    collider_ = Collider::addColliderComponent(this, sprite_move_->getSize(),sprite_move_->getOffset());

    sprite_cur_ = sprite_move_;
    
}

void Enemy::update(float dt)
{
    Actor::update(dt); // 调用父类的更新方法

    updateVelocityTowardsTarget(); // 更新敌人速度以追踪玩家
    move(dt); // 根据速度移动敌人
    checkState(); // 检查敌人状态
    TryAttackTarget(); // 检查是否攻击玩家
    checkIsPendingKill();
}

void Enemy::changeState(EnemyState newState)
{
    if (cur_state_ == newState) return; // 如果状态没有变化，直接返回

    sprite_cur_->setActive(false);
    switch (newState)
    {
    case EnemyState::MOVE:
        sprite_cur_ = sprite_move_;
        break;
    case EnemyState::HURT:
        sprite_cur_ = sprite_hurt_;
        break;
    case EnemyState::DEAD:
        sprite_cur_ = sprite_dead_;
        break;
    default:
        break;
    }
    sprite_cur_->setActive(true);
    cur_state_ = newState;
}

void Enemy::checkState()
{
}

void Enemy::updateVelocityTowardsTarget()
{
    if (!target_) return; // 如果没有目标玩家，直接返回

    glm::vec2 direction = target_->getPosition() - getPosition(); // 计算敌人到玩家的方向向量
    setVelocity(glm::normalize(direction) * getMaxSpeed()); // 设置敌人的速度为最大速度，方向指向玩家

}

void Enemy::checkIsPendingKill()
{
    // 如果当前精灵动画已经播放完毕，并且敌人处于死亡状态，则将敌人标记为待删除
    if(sprite_cur_->isFinish())
    {
        this->setPendingKill(true); // 标记敌人为待删除状态
    }
}

void Enemy::TryAttackTarget()
{
    if (!target_ || !collider_ || !target_->getCollider()) return; // 如果没有目标玩家或敌人没有碰撞体，直接返回
    bool isCollision = target_->getCollider()->checkCollision(*collider_); // 检查敌人和玩家的碰撞
    if (isCollision)
    {
        // 如果发生碰撞，执行攻击逻辑
        // 这里可以添加攻击玩家的代码，例如减少玩家的生命值等
        printf("Enemy attacks the player!");
    }
}
