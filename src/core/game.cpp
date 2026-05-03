#include "game.h"

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
            dt_ = frameDelay_ / 1e9; // 转换为秒
        }else{
            dt_ = elapsedTime / 1e9; // 转换为秒
        }
        SDL_Log("FPS: %f", 1.0 / dt_);
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
    frameDelay_ = 1e9 / FPS_; // 转换为纳秒
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
            break;
        }
    }
}

void Game::update(float dt)
{
    
}

void Game::render()
{
    
}

void Game::clean()
{
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