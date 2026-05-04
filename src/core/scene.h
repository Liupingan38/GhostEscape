#pragma once

#include "object.h"
#include<glm/glm.hpp>
#include<vector>


class Scene : public Object
{
protected:
    glm::vec2 cameraPos_ = glm::vec2(0.f, 0.f);
    std::vector<Object*> sceneObjects_;

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {}
    virtual void handleEvents(SDL_Event &event) override {}
    virtual void update(float dt) override {}
    virtual void render() override {}
    virtual void clean() override {}

    // getter and setter
    const glm::vec2& getCameraPos() const { return cameraPos_; }
    void setCameraPos(const glm::vec2& pos) { cameraPos_ = pos; }

    // 屏幕坐标转换为世界坐标
    glm::vec2 screenToWorld(const glm::vec2& screenPos) const{return screenPos + cameraPos_;}
    // 世界坐标转换为屏幕坐标
    glm::vec2 worldToScreen(const glm::vec2& worldPos) const{return worldPos - cameraPos_;}
    
};