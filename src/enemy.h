#pragma once
#include "core/actor.h"
#include "player.h"  // player.h 中已经包含了 spriteAnim.h，因此不需要再次包含

class Enemy : public Actor
{
private:
    enum class EnemyState
    {
        MOVE,
        HURT,
        DEAD
    };
    Player* target_ = nullptr; // 指向玩家对象的指针
    SpriteAnim *sprite_move_ = nullptr;
    SpriteAnim *sprite_hurt_ = nullptr;
    SpriteAnim *sprite_dead_ = nullptr;

    SpriteAnim *sprite_cur_ = nullptr; // 当前精灵动画
    EnemyState cur_state_ = EnemyState::MOVE;


public:
    Enemy() = default;
    virtual ~Enemy() = default;

    static Enemy* addEnemyChild(Object* parent, Player* target, const glm::vec2& position);

    virtual void init() override;
    //virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    //virtual void render() override;
    //virtual void clean() override;

    void changeState(EnemyState newState); // 改变敌人状态
    void checkState(); // 检查敌人状态
    void updateVelocityTowardsTarget(); // 更新敌人速度以追踪玩家
    void checkIsPendingKill(); // 被标记后，下一帧删除，下一帧就不会再调用update了
    void TryAttackTarget(); // 攻击玩家

    // getter and setter
    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }
};