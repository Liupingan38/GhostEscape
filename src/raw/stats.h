#pragma once
#include "../core/object.h"
#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor* parent_ = nullptr; // 拥有者
    float health_ = 100.f;
    float mana_ = 100.f;
    float healthMax_ = 100.f;
    float manaMax_ = 100.f;
    float manaRegen_ = 1.f;
    float attack_ = 10.f;

    bool isAlive_ = true;
    bool isInvincible_ = false;
    float invincibleTime_ = 1.0f;
    float invincibleTimer_ = 0.f;
public:
    Stats() = default;
    virtual ~Stats() = default;

    static Stats* addStatsComponent(Actor* parent, float health=100.f,float mana=100.f,float healthMax=100.f,float manaMax=100.f,float manaRegen=1.f,float attack=10.f);

    virtual void update(float dt) override;

    bool canUseMana(float amount) const { return mana_ >= amount; }
    void useMana(float amount);
    void regenerateMana(float dt);
    void takeDamage(float damage);
    void checkIsInvincible(float dt);


    // getter and setter
    Actor* getParent() const { return parent_; }
    void setParent(Actor* parent) { parent_ = parent; }
    float getHealth() const { return health_; }
    void setHealth(float h) { health_ = h; }
    float getMana() const { return mana_; }
    void setMana(float m) { mana_ = m; }
    float getHealthMax() const { return healthMax_; }
    void setHealthMax(float hMax) { healthMax_ = hMax; }
    float getManaMax() const { return manaMax_; }
    void setManaMax(float mMax) { manaMax_ = mMax; }
    float getManaRegen() const { return manaRegen_; }
    void setManaRegen(float mRegen) { manaRegen_ = mRegen; }
    float getAttack() const { return attack_; }
    void setAttack(float atk) { attack_ = atk; }
    bool getIsAlive() const { return isAlive_; }
    void setIsAlive(bool alive) { isAlive_ = alive; }
    bool getIsInvincible() const { return isInvincible_; }
    void setIsInvincible(bool invincible) { isInvincible_ = invincible; }

};