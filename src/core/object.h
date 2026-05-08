#pragma once

#include "game.h"
#include<vector>


class Object
{
protected:
    Game& game_ = Game::getInstance();
    std::vector<Object*> children_; // 子对象列表

public:
    Object() = default;
    virtual ~Object() = default;

    virtual void init() ;
    virtual void handleEvents(SDL_Event &event) ;
    virtual void update(float dt) ;
    virtual void render() ;
    virtual void clean() ;

    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());}
    
};