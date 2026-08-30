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
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, 
        float scale = 1.0f, bool bCentered = false);

    void setScale(float scale) { size_ *= scale; }

    // getter and setter
    Texture getTexture() const { return texture_; }
    virtual void setTexture(Texture texture) ;

    virtual void render() override;
};