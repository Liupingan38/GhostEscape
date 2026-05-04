#include "assetStore.h"


void AssetStore::loadTexture(const std::string &filePath)
{
    //  加载图片资源
    SDL_Texture* texture = IMG_LoadTexture(game_.getRenderer(), filePath.c_str());
    if (!texture)
    {
        SDL_Log("Failed to load texture: %s", SDL_GetError());
        return;
    }
    textures_.emplace(filePath, texture);
}

void AssetStore::loadAudio(const std::string &filePath, bool predecode)
{
    // 加载音乐资源(预解码适合短音效，非预解码适合长音乐)
    MIX_Audio* audio = MIX_LoadAudio(game_.getMixer(),filePath.c_str(), predecode);
    if (!audio)
    {
        SDL_Log("Failed to load audio: %s", SDL_GetError());
        return;
    }
    audios_.emplace(filePath, audio);
}

void AssetStore::loadFont(const std::string &filePath, int fontSize)
{
    // 加载字体资源
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return;
    }
    std::string key = filePath + std::to_string(fontSize);
    fonts_.emplace(key, font);
}

void AssetStore::clean()
{
    // 清理图片资源
    for (auto &pair : textures_)
    {
        SDL_DestroyTexture(pair.second);
    }
    textures_.clear();

    // 清理音乐资源
    for (auto &pair : audios_)
    {
        MIX_DestroyAudio(pair.second);
    }
    audios_.clear();

    // 清理字体资源
    for (auto &pair : fonts_)
    {
        TTF_CloseFont(pair.second);
    }
    fonts_.clear();
}

SDL_Texture *AssetStore::getTexture(const std::string &filePath)
{
    auto it = textures_.find(filePath);
    // 如果资源不存在，尝试加载
    if (it == textures_.end()){ 
        loadTexture(filePath);
        it = textures_.find(filePath);
    }
    // 如果加载后仍然不存在，返回nullptr
    if(it==textures_.end()) 
    {
        SDL_Log("Failed to get texture: %s", SDL_GetError());
        return nullptr;
    }
    return it->second;
}

MIX_Audio *AssetStore::getAudio(const std::string &filePath, bool predecode)
{
    auto it = audios_.find(filePath);
    // 如果资源不存在，尝试加载
    if (it == audios_.end())
    {
        loadAudio(filePath, predecode);
        it = audios_.find(filePath);
    }
    // 如果加载后仍然不存在，返回nullptr
    if (it == audios_.end())
    {
        SDL_Log("Failed to get audio: %s", SDL_GetError());
        return nullptr;
    }
    return it->second;
}

TTF_Font *AssetStore::getFont(const std::string &filePath, int fontSize)
{
    std::string key = filePath + std::to_string(fontSize);
    auto it = fonts_.find(key);
    // 如果资源不存在，尝试加载
    if (it == fonts_.end())
    {
        loadFont(filePath, fontSize);
        it = fonts_.find(key);
    }
    // 如果加载后仍然不存在，返回nullptr
    if (it == fonts_.end())
    {
        SDL_Log("Failed to get font: %s", SDL_GetError());
        return nullptr;
    }
    return it->second;
}
