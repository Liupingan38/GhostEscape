#include "sceneMain.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"

void SceneMain::init()
{
    Scene::init(); // 调用父类的初始化方法

    setCameraPosition((getWorldSize()-game_.getScreenSize())/2.f); // 初始化摄像机位置

    // 创建玩家对象并添加到场景中
    player_ = new Player();
    player_->init();
    player_->setPosition(getWorldSize()/2.f); // 玩家初始位置在世界中心
    addChild(player_); // 将玩家对象添加到场景中

    // 创建生成器对象并添加到场景中
    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTargetPlayer(player_); // 设置生成器的目标玩家对象
    addChild(spawner_); // 将生成器对象添加到场景中
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event); // 调用父类的事件处理方法
}

void SceneMain::update(float dt)
{
    Scene::update(dt); // 调用父类的更新方法

    //cameraPos_ += glm::vec2(200.f, 300.f) * dt; // 模拟摄像机向右移动
    
}

void SceneMain::render()
{
    renderBackground();
    Scene::render(); // 调用父类的渲染方法
    
}

void SceneMain::clean()
{
    Scene::clean(); // 调用父类的清理方法

}

void SceneMain::renderBackground()
{
    // 计算网格的起始和结束位置（每次都绘制整个世界，SDL进行裁剪）
    glm::vec2 start=-cameraPosition_;
    glm::vec2 end=wordSize_-cameraPosition_;
    game_.drawGrid(start,end, gridWidth_, gridColor_);// 绘制网格
    game_.drawRect(start,end, borderWidth_, gridColor_); // 绘制世界边界
}
