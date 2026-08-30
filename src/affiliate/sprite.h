#pragma once

#include "../core/objectAffiliate.h"
#include <string>

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = {0.f, 0.f, 0.f, 0.f};
    float angle = 0.f;
    bool is_flip = false;
    Texture() = default;
    Texture(const std::string& file_path);
};

class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;

public:
    // getter and setter
    Texture getTexture() const { return texture_; }
    void setTexture(Texture texture) ;

    void render() ;
};