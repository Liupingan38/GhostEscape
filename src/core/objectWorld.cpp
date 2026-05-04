#include "objectWorld.h"
#include"scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt); // 先调用父类的update
    
    // 根据世界坐标更新屏幕坐标
    screenPosition_ = game_.getCurrentScene()->worldToScreen(position_);
}

void ObjectWorld::setPosition(const glm::vec2 &pos)
{
    position_ = pos;
    // 根据世界坐标更新屏幕坐标
    screenPosition_ = game_.getCurrentScene()->worldToScreen(position_);
}

void ObjectWorld::setScreenPosition(const glm::vec2 &pos)
{
    screenPosition_ = pos;
    // 根据屏幕坐标更新世界坐标
    position_ = game_.getCurrentScene()->screenToWorld(screenPosition_);
}
