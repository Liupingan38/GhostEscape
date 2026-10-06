#pragma once
#include "core/object.h"

class Player;
class Spawner :public Object
{
private:
    int spawn_count_ = 10; 
    float spawn_interval_ = 3.0f; // 每次生成的间隔时间，单位为秒
    float spawn_timer_ = 0.0f; // 计时器，用于记录生成的时间
    Player* target_player_ = nullptr; // 目标玩家对象指针
public:
    void update(float dt) override;

    // getter and setter
    int getSpawnCount() const { return spawn_count_; }
    void setSpawnCount(int count) { spawn_count_ = count; }
    float getSpawnInterval() const { return spawn_interval_; }
    void setSpawnInterval(float interval) { spawn_interval_ = interval; }
    Player* getTargetPlayer() const { return target_player_; }
    void setTargetPlayer(Player* player) { target_player_ = player; }


};