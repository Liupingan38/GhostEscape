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
    bool is_finish_ = false; // 是否播放完毕（用于动画精灵）

public:
    static Sprite* addSpriteComponent(ObjectScreen* parent, const std::string& file_path, 
        float scale = 1.0f, AnchorType anchor = AnchorType::ANCHOR_CENTER);


    // getter and setter
    Texture getTexture() const { return texture_; }
    virtual void setTexture(Texture texture) ;
    float getAngle() const { return texture_.angle; }
    void setAngle(float angle) { texture_.angle = angle; }
    bool isFlip() const { return texture_.is_flip; }
    void setFlip(bool flip) { texture_.is_flip = flip; }
    bool isFinish() const { return is_finish_; }
    void setFinish(bool finish) { is_finish_ = finish; }

    virtual void render() override;
};