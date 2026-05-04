#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include "game.h"

class AssetStore
{
private:
    Game& game_ = Game::getInstance();    

    std::unordered_map<std::string, SDL_Texture *> textures_;
    std::unordered_map<std::string, MIX_Audio *> audios_;
    std::unordered_map<std::string, TTF_Font *> fonts_;

    // 加载资源
    void loadTexture(const std::string &filePath);
    void loadAudio(const std::string &filePath,bool predecode=false);//默认不预解码，适合长音乐
    void loadFont(const std::string &filePath, int fontSize);

public:
    AssetStore()=default;
    ~AssetStore() = default;

    void clean();

    // 获取资源
    SDL_Texture *getTexture(const std::string &filePath);
    MIX_Audio *getAudio(const std::string &filePath,bool predecode=false);
    TTF_Font *getFont(const std::string &filePath, int fontSize);
};