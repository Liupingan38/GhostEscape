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

    virtual void init() override {};
    virtual void handleEvents(SDL_Event &event) override {};
    virtual void update(float dt) override {};
    virtual void render() override {};
    virtual void clean() override {};
};