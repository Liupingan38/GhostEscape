#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

class Scene;
class AssetStore;

class Game
{
private:

    //游戏资源管理
    AssetStore *assetStore_ = nullptr;

    // 游戏场景相关
    Scene *currentScene_ = nullptr;

    // 游戏初始化相关
    bool isRunning_ = true;
    glm::vec2 screenSize_ = glm::vec2(1080, 720);

    // SDL相关
    SDL_Window *window_=nullptr;
    SDL_Renderer *renderer_=nullptr;
    MIX_Mixer *mixer_ = nullptr;

    // 游戏帧率相关
    Uint64 FPS_=120;            // 目标帧率
    Uint64 frameDelay_ = 0;    // 每帧应该花的时间（纳秒）
    float dt_ = 0.f;           // 每帧实际花的时间（秒）

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

    // 绘制网格
    void drawGrid(const glm::vec2& left_top, const glm::vec2& right_bottom, float gridWidth, SDL_FColor color);

    //绘制方框
    void drawRect(const glm::vec2& left_top, const glm::vec2& right_bottom, float width,SDL_FColor color);

    // getter and setter (如果只有一行，编译器会优化成inline函数)
    Scene* getCurrentScene() const { return currentScene_; }
    void setCurrentScene(Scene* scene) { currentScene_ = scene; }
    const glm::vec2& getScreenSize() const { return screenSize_; }
    void setScreenSize(const glm::vec2& size) { screenSize_ = size; }
    SDL_Renderer* getRenderer() const { return renderer_; }
    MIX_Mixer* getMixer() const { return mixer_; }
    AssetStore* getAssetStore() const { return assetStore_; }
};