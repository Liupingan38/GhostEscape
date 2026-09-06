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
    for (auto it = children_.begin(); it != children_.end(); )
    {
        auto child = *it;
        if(child->isPendingKill()){
            child->clean();
            delete child;
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
    }
    children_.clear();
}