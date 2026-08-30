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
    for (auto& child : children_)
    {
        if (!child->isActive()) continue;
        child->update(dt);
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