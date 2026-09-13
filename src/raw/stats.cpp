#include "stats.h"

Stats *Stats::addStatsComponent(Actor *parent, float health, float mana, float healthMax, float manaMax, float manaRegen, float attack)
{
    Stats *stats = new Stats();
    stats->init();
    stats->setParent(parent);
    stats->setHealth(health);
    stats->setMana(mana);
    stats->setHealthMax(healthMax);
    stats->setManaMax(manaMax);
    stats->setManaRegen(manaRegen);
    stats->setAttack(attack);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    
    checkIsInvincible(dt);
    regenerateMana(dt);
}

void Stats::useMana(float amount)
{
    if (canUseMana(amount)) {
        mana_ -= amount;
    }
}

void Stats::regenerateMana(float dt)
{
    mana_ += manaRegen_ * dt;
    if(mana_ > manaMax_) mana_ = manaMax_;
}

void Stats::takeDamage(float damage)
{
    if (isInvincible_) return;

    if (damage <= 0) return;
    health_ -= damage;
    
    if (health_ <= 0) {
        health_ = 0;
        isAlive_ = false;
    }
    printf("Health: %f\n", health_);
    
    isInvincible_ = true;
    invincibleTimer_ = 0.0f;
}

void Stats::checkIsInvincible(float dt)
{
    if (isInvincible_) {
        invincibleTimer_ += dt;
        if (invincibleTimer_ >= invincibleTime_) {
            isInvincible_ = false;
        }
    }
}
