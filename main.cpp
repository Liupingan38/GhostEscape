#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

int main(int, char**) {
    

    std::cout << "Hello, World!" << std::endl;
    // SDL初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Hello World!", 800, 600, 0);
    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    // SDL3_Image不需要手动初始化

    // 加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/UI/Green Potion.png");

    // SDL_Mixer初始化
    if (!MIX_Init()) {
        std::cerr << "MIX_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 创建Mixer
    MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,NULL);
    // 创建音轨
    MIX_Track *music_track=MIX_CreateTrack(mixer);
    // 加载音乐
    MIX_Audio *music_data = MIX_LoadAudio(mixer,"assets/sound/UI_button08.wav",false);
    // 将音乐数据添加到音轨
    MIX_SetTrackAudio(music_track,music_data);

    // 播放音乐
    SDL_PropertiesID options = SDL_CreateProperties();
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1); // 设置循环次数，-1表示无限循环
    MIX_PlayTrack(music_track,options);


    // SDL_TTF初始化
    if (!TTF_Init()) {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);

    // SDL2的创建文本纹理
    SDL_Color color = {255, 255, 255, 255};
    const char *text = "Hello, SDL! 我淦";
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, 0, color); 
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    // SDL3的创建文本纹理
    TTF_TextEngine *textEngine = TTF_CreateRendererTextEngine(renderer);
    TTF_Text *ttfText = TTF_CreateText(textEngine,  font, text,0);
    TTF_SetTextColor(ttfText, 255, 255, 0, 255);

    glm::vec2 mousePos=glm::vec2(0.0f,0.0f);

    // Do something with the window and renderer here...
    // 渲染循环
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                break;
            }
        }

        auto state = SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if(state & (1<<(SDL_BUTTON_LEFT-1))){
            std::cout<<"Mouse Left"<<std::endl;
        }
        if(state & (1<<(SDL_BUTTON_RIGHT-1))){
            std::cout<<"Mouse Right"<<std::endl;
        }

        // 清屏
        SDL_RenderClear(renderer);
        // 设置绘制颜色
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // 画一个长方形
        SDL_FRect rect = {100, 100, 200, 200};
        SDL_RenderFillRect(renderer, &rect);
        

        // 画图片
        SDL_FRect dstrect = {200, 200, 200, 200};
        SDL_RenderTexture(renderer, texture, NULL, &dstrect);

        // 画文本(SDL2)
        SDL_FRect textRect = {300, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        // 画文本(SDL3)
        TTF_DrawRendererText(ttfText, 400, 400);

        // 设置绘制颜色为黑色
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

        // 更新屏幕
        SDL_RenderPresent(renderer);
        

        
    }

    // 清理图片资源
    SDL_DestroyTexture(texture);

    // 清理音乐资源
    MIX_DestroyAudio(music_data);
    MIX_DestroyTrack(music_track);
    MIX_DestroyMixer(mixer);
    MIX_Quit();


    // 清理字体资源
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // 清理并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}