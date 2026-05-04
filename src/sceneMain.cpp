#include "sceneMain.h"
#include "player.h"

void SceneMain::init()
{
    setCameraPosition((getWorldSize()-game_.getScreenSize())/2.f); // 初始化摄像机位置

    // 创建玩家对象并添加到场景中
    player_ = new Player();
    player_->setPosition(getWorldSize()/2.f); // 玩家初始位置在世界中心
}

void SceneMain::handleEvents(SDL_Event &event)
{
}

void SceneMain::update(float dt)
{
    //cameraPos_ += glm::vec2(200.f, 300.f) * dt; // 模拟摄像机向右移动
    player_->update(dt); // 更新玩家对象
}

void SceneMain::render()
{
    renderBackground();
    player_->render(); // 渲染玩家对象
}

void SceneMain::clean()
{
    if(player_) 
    {
        player_->clean();
        delete player_;
        player_ = nullptr;
    }
}

void SceneMain::renderBackground()
{
    // 计算网格的起始和结束位置（每次都绘制整个世界，SDL进行裁剪）
    glm::vec2 start=-cameraPosition_;
    glm::vec2 end=wordSize_-cameraPosition_;
    game_.drawGrid(start,end, gridWidth_, gridColor_);// 绘制网格
    game_.drawRect(start,end, borderWidth_, gridColor_); // 绘制世界边界
}
