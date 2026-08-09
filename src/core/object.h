#pragma once

#include "game.h"
#include "defs.h"
#include<vector>


class Object
{
protected:
    Game& game_ = Game::getInstance();
    std::vector<Object*> children_; // 子对象列表
    ObjectType type_ = ObjectType::OBJECT_NONE; // 对象类型

public:
    Object() = default;
    virtual ~Object() = default;

    virtual void init() {}
    virtual void handleEvents(SDL_Event &event) ;
    virtual void update(float dt) ;
    virtual void render() ;
    virtual void clean() ;

    // getter and setter
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }

    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());}
    
};