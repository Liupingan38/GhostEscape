#include "game.h"
#include"../sceneMain.h"
#include"../player.h"

Game::~Game()
{
    clean();
}

void Game::run()
{
    // 游戏主循环
    while (isRunning_)
    {   
        Uint64 startTime = SDL_GetTicksNS();
        handleEvents();
        update(dt_); 
        render();
        Uint64 endTime = SDL_GetTicksNS();
        Uint64 elapsedTime = endTime - startTime; //实际这一帧跑了多久（CPU真实耗时,ns）
        if(elapsedTime < frameDelay_) 
        {
            SDL_DelayNS(frameDelay_ - elapsedTime); 
            dt_ = static_cast<float>(frameDelay_ / 1e9); // 转换为秒
        }else{
            dt_ = static_cast<float>(elapsedTime / 1e9); // 转换为秒
        }
        
    }
}

void Game::init(std::string title, int width, int height)
{
    

    // 初始化SDL3
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        isRunning_ = false;
        return;
    }

    // SDL3_image不用初始化

    // 初始化SDL3_mixer
    if (!MIX_Init())
    {
        std::cerr << "Failed to initialize SDL_mixer: " << SDL_GetError() << std::endl;
        isRunning_ = false;
        return;
    }
    
    // 初始化SDL3_ttf
    if (!TTF_Init())
    {
        std::cerr << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
        isRunning_ = false;
        return;
    }

    // 创建窗口和渲染器
    screenSize_ = glm::vec2(width, height);
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);

    if (!window_ || !renderer_)
    {
        std::cerr << "Failed to create window or renderer: " << SDL_GetError() << std::endl;
        isRunning_ = false;
        return;
    }

    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 计算游戏帧间隔
    frameDelay_ = static_cast<Uint64>(1e9 / FPS_); // 转换为纳秒

    // 初始化游戏场景
    currentScene_ = new SceneMain();
    currentScene_->init();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // 点击关闭按钮退出游戏
        case SDL_EVENT_QUIT:
            isRunning_ = false;
            break;
        // 处理其他事件，如键盘输入、鼠标事件等
        default:
            if(currentScene_) currentScene_->handleEvents(event);

            break;
        }
    }
}

void Game::update(float dt)
{
    // 更新当前场景
    if(currentScene_) currentScene_->update(dt);
}

void Game::render()
{
    // 清屏
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    // 渲染当前场景
    if(currentScene_) currentScene_->render();

    // 显示渲染结果
    SDL_RenderPresent(renderer_);

}

void Game::clean()
{
    // 清理游戏场景
    if(currentScene_) 
    {
        currentScene_->clean();
        delete currentScene_;
        currentScene_ = nullptr;
    }

    // 清理图片资源
    

    // 清理音乐资源
    
    MIX_Quit();


    // 清理字体资源
    
    TTF_Quit();

    // 清理并退出
    if(renderer_) SDL_DestroyRenderer(renderer_);
    if(window_) SDL_DestroyWindow(window_);
    SDL_Quit();
    
}

void Game::drawGrid(const glm::vec2& left_top, const glm::vec2& right_bottom, float gridWidth, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);

    // 绘制竖线
    for (float x = left_top.x; x <= right_bottom.x; x += gridWidth)
    {
        SDL_RenderLine(renderer_, x, left_top.y, x, right_bottom.y);
    }

    // 绘制横线
    for (float y = left_top.y; y <= right_bottom.y; y += gridWidth)
    {
        SDL_RenderLine(renderer_, left_top.x, y, right_bottom.x, y);
    }

    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1); // 恢复默认颜色
}

void Game::drawRect(const glm::vec2 &left_top, const glm::vec2 &right_bottom, float width, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);

    // 绘制边框
    for (int i = 0; i < width; ++i)
    {
        SDL_FRect rect = {left_top.x - i, left_top.y - i, right_bottom.x - left_top.x + 2 * i, right_bottom.y - left_top.y + 2 * i};
        SDL_RenderRect(renderer_, &rect);
    }

    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1); // 恢复默认颜色
}
