#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    for (auto& child : children_)
    {
        if (!child->isActive()) continue;
        child->handleEvents(event);
    }
}

void Object::update(float dt)
{
    // 先把前一帧的物体加入进来，同时保持在update中加入的物体，都使用addChlidSafe，这样会在下一帧处理。
    for (auto& child:object_to_add_){
        addChild(child);
    }
    object_to_add_.clear();

    for (auto it = children_.begin(); it != children_.end(); )
    {
        auto child = *it;
        if(child->isPendingKill()){
            child->clean();
            delete child;
            child = nullptr;
            it = children_.erase(it);
        }else{
            if (child->isActive()) child->update(dt);
            ++it;
        }
    }
}

void Object::render()
{
    for (auto& child : children_)
    {
        if (!child->isActive()) continue;
        child->render();
    }
}

void Object::clean()
{
    for (auto& child : children_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_.clear();
}