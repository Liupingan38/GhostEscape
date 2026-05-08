#include "scene.h"

void Scene::addChild(Object *child)
{
}

void Scene::removeChild(Object *child)
{
}

void Scene::setCameraPosition(const glm::vec2 &pos)
{
    cameraPosition_ = pos;
    // 限制摄像机在世界边界内
    cameraPosition_ = glm::clamp(cameraPosition_, -cameraBorderOffset_, wordSize_ - game_.getScreenSize()+cameraBorderOffset_);
}