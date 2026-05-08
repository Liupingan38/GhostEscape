#pragma once

#include "object.h"
#include "objectWorld.h"
#include<glm/glm.hpp>
#include<vector>


class Scene : public Object
{
private:
    glm::vec2 cameraBorderOffset_=glm::vec2(100.f,100.f); // 摄像机外溢边界
protected:
    glm::vec2 wordSize_=glm::vec2(3000.f, 2000.f);
    glm::vec2 cameraPosition_ = glm::vec2(0.f, 0.f);

    std::vector<ObjectScreen*> screenChildren_; // 屏幕对象列表
    std::vector<ObjectWorld*> worldChildren_; // 世界对象列表
    

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {}
    virtual void handleEvents(SDL_Event &event) override {}
    virtual void update(float dt) override {}
    virtual void render() override {}
    virtual void clean() override {}

    virtual void addChild(Object* child) override;
    virtual void removeChild(Object* child) override;

    // getter and setter
    const glm::vec2& getCameraPosition() const { return cameraPosition_; }
    void setCameraPosition(const glm::vec2& pos) ;
    const glm::vec2& getWorldSize() const { return wordSize_; }
    void setWorldSize(const glm::vec2& size) { wordSize_ = size; }

    // 屏幕坐标转换为世界坐标
    glm::vec2 screenToWorld(const glm::vec2& screenPos) const{return screenPos + cameraPosition_;}
    // 世界坐标转换为屏幕坐标
    glm::vec2 worldToScreen(const glm::vec2& worldPos) const{return worldPos - cameraPosition_;}

};