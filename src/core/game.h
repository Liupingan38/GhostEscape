#pragma once

#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

class Scene;

class Game
{
private:

    // 游戏场景相关
    Scene *currentScene_ = nullptr;

    // 游戏初始化相关
    bool isRunning_ = true;
    glm::vec2 screenSize_ = glm::vec2(1080, 720);
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    // 游戏帧率相关
    Uint64 FPS_=120;            // 目标帧率
    Uint64 frameDelay_ = 0;    // 每帧应该花的时间（纳秒）
    float dt_ = 0.f;           // 每帧实际花的时间（秒）

private:
    Game() {};
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    

public:
    ~Game();

    static Game &getInstance()
    {
        static Game instance;
        return instance;
    }


    void run();
    void init(std::string title, int width, int height);
    void handleEvents();
    void update(float dt);
    void render();
    void clean();
};