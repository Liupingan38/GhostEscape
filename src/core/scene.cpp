#include "scene.h"

void Scene::handleEvents(SDL_Event &event)
{
    Object::handleEvents(event); // 调用父类的事件处理方法
    for (auto child : screenChildren_)
    {
        child->handleEvents(event);
    }
    for (auto child : worldChildren_)
    {
        child->handleEvents(event);
    }
}

void Scene::update(float dt)
{
    Object::update(dt); // 调用父类的更新方法
    for (auto child : worldChildren_)
    {
        child->update(dt);
    }
    for (auto child : screenChildren_)
    {
        child->update(dt);
    }
    
}

void Scene::render()
{
    Object::render(); // 调用父类的渲染方法
    for (auto child : worldChildren_)
    {
        child->render();
    }
    for (auto child : screenChildren_)
    {
        child->render();
    }
}

void Scene::clean()
{
    Object::clean(); // 调用父类的清理方法
    for (auto child : screenChildren_)
    {
        child->clean();
        delete child;
    }
    screenChildren_.clear();
    for (auto child : worldChildren_)
    {
        child->clean();
        delete child;
    }
    worldChildren_.clear();
}

void Scene::addChild(Object *child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_SCREEN:
            screenChildren_.push_back(static_cast<ObjectScreen*>(child)); //使用dynamic_cast的话会开启RTTI，增加开销，且不成功的时候会返回nullptr
            break;
        case ObjectType::OBJECT_WORLD:
            worldChildren_.push_back(static_cast<ObjectWorld*>(child));
            break;
        default:
            children_.push_back(child);
            break;   
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {
        case ObjectType::OBJECT_SCREEN:
            screenChildren_.erase(std::remove(screenChildren_.begin(), screenChildren_.end(), child), screenChildren_.end());
            break;
        case ObjectType::OBJECT_WORLD:
            worldChildren_.erase(std::remove(worldChildren_.begin(), worldChildren_.end(), child), worldChildren_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
            break;   
    }
}

void Scene::setCameraPosition(const glm::vec2 &pos)
{
    cameraPosition_ = pos;
    // 限制摄像机在世界边界内
    cameraPosition_ = glm::clamp(cameraPosition_, -cameraBorderOffset_, wordSize_ - game_.getScreenSize()+cameraBorderOffset_);
}