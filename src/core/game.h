#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <random>

class Scene;
class AssetStore;
struct Texture;

class Game
{
private:

    //游戏资源管理
    AssetStore *assetStore_ = nullptr;

    // 游戏场景相关
    Scene *currentScene_ = nullptr;

    // 游戏初始化相关
    bool isRunning_ = true;
    glm::vec2 screenSize_ = glm::vec2(720, 640);

    // SDL相关
    SDL_Window *window_=nullptr;
    SDL_Renderer *renderer_=nullptr;
    MIX_Mixer *mixer_ = nullptr;

    // 游戏帧率相关
    Uint64 FPS_=120;            // 目标帧率
    Uint64 frameDelay_ = 0;    // 每帧应该花的时间（纳秒）
    float dt_ = 0.f;           // 每帧实际花的时间（秒）

    // 随机数生成器
    std::mt19937 gen_ = std::mt19937(std::random_device{}()); 

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

    // 渲染Texture
    void renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size);

    // 渲染填充圆
    void renderFilledCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha = 1.0f);
    
    // 绘制网格
    void drawGrid(const glm::vec2& left_top, const glm::vec2& right_bottom, float gridWidth, SDL_FColor color);

    //绘制方框
    void drawRect(const glm::vec2& left_top, const glm::vec2& right_bottom, float width,SDL_FColor color);

    // 在某一个分布上生成随机数
    int getRandomInt(int min, int max) {return std::uniform_int_distribution<int>(min, max)(gen_);}
    float getRandomFloat(float min, float max){return std::uniform_real_distribution<float>(min, max)(gen_);}
    glm::vec2 getRandomVec2(const glm::vec2& min, const glm::vec2& max){return glm::vec2(getRandomFloat(min.x, max.x), getRandomFloat(min.y, max.y));}
    glm::ivec2 getRandomIVec2(const glm::ivec2& min, const glm::ivec2& max){return glm::ivec2(getRandomInt(min.x, max.x), getRandomInt(min.y, max.y));}

    // getter and setter (如果只有一行，编译器会优化成inline函数)
    Scene* getCurrentScene() const { return currentScene_; }
    void setCurrentScene(Scene* scene) { currentScene_ = scene; }
    const glm::vec2& getScreenSize() const { return screenSize_; }
    void setScreenSize(const glm::vec2& size) { screenSize_ = size; }
    SDL_Renderer* getRenderer() const { return renderer_; }
    MIX_Mixer* getMixer() const { return mixer_; }
    AssetStore* getAssetStore() const { return assetStore_; }
};