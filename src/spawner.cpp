#include "spawner.h"
#include "enemy.h"
#include "core/scene.h"
#include "world/effect.h"

void Spawner::update(float dt)
{
    if (!target_player_ || !target_player_->isActive()) return; // 如果没有目标玩家或玩家不活跃，直接返回
    spawn_timer_ += dt; // 累加时间

    // 如果计时器超过了生成间隔时间，则生成新的敌人
    if (spawn_timer_ >= spawn_interval_)
    {
        spawn_timer_ = 0.0f; // 重置计时器

        // 生成指定数量的敌人
        for (int i = 0; i < spawn_count_; ++i)
        {
            // 设置敌人的初始位置为随机位置
            glm::vec2 left_top = Game::getInstance().getCurrentScene()->getCameraPosition();
            glm::vec2 spawn_position = Game::getInstance().getRandomVec2(left_top, left_top + Game::getInstance().getScreenSize());
            // 生成敌人对象
            Enemy* enemy = Enemy::addEnemyChild(nullptr, target_player_, spawn_position);
            // 生成特效对象，并在特效播放完后将敌人加入场景
            Effect::addEffectChild(Game::getInstance().getCurrentScene(), "assets/effect/184_3_.png", enemy, spawn_position);
        }
    }
}
