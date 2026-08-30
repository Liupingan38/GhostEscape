#pragma once
#include "sprite.h"

class SpriteAnim : public Sprite
{

private:
    int cur_frame_ = 0;
    int total_frame_ = 0;
    int FPS = 10; 
    float time_counter_ = 0.0f;
public:
    static SpriteAnim* addSpriteAnimChild(ObjectScreen* parent, const std::string& file_path, 
        float scale=1.0f, bool bCentered = false,int fps = 10);

    void update(float dt);
    virtual void setTexture(Texture texture) override;
};