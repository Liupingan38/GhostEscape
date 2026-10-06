#pragma once

#include "game.h"
#include "defs.h"
#include<vector>


class Object
{
protected:
    Game& game_ = Game::getInstance();
    std::vector<Object*> children_; // 子对象列表
    std::vector<Object*> object_to_add_; //暂存对象，安全添加到子对象列表
    ObjectType type_ = ObjectType::OBJECT_NONE; // 对象类型
    bool is_active_ = true; // 对象是否激活
    bool is_pending_kill_ = false; // 对象是否待删除
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
    bool isActive() const { return is_active_; }
    void setActive(bool active) { is_active_ = active; }
    bool isPendingKill() const { return is_pending_kill_; }
    void setPendingKill(bool pending) { is_pending_kill_ = pending; }

    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void addChildSafe(Object* child) { object_to_add_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());}
    
};