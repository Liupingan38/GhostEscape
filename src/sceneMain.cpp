#include "sceneMain.h"

void SceneMain::init()
{
}

void SceneMain::handleEvents(SDL_Event &event)
{
}

void SceneMain::update(float dt)
{
    cameraPos_ += glm::vec2(200.f, 300.f) * dt; // 模拟摄像机向右移动
}

void SceneMain::render()
{
    renderBackground();
}

void SceneMain::clean()
{
}

void SceneMain::renderBackground()
{
    // 计算网格的起始和结束位置（每次都绘制整个世界，SDL进行裁剪）
    glm::vec2 start=-cameraPos_;
    glm::vec2 end=wordSize_-cameraPos_;
    game_.drawGrid(start,end, gridWidth_, gridColor_);// 绘制网格
    game_.drawRect(start,end, borderWidth_, gridColor_); // 绘制世界边界
}
