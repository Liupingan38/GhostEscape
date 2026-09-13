#pragma once
#include "sprite.h"

class SpriteAnim : public Sprite
{

private:
    int cur_frame_ = 0;
    int total_frame_ = 0;
    int FPS = 10; 
    float time_counter_ = 0.0f;

    bool  is_loop_ = true; // 是否循环播放动画
    
public:
    static SpriteAnim* addSpriteAnimComponent(ObjectScreen* parent, const std::string& file_path, 
        float scale=1.0f, bool bCentered = false,int fps = 10);

    void update(float dt);
    virtual void setTexture(Texture texture) override;

    // getter and setter
    int getCurFrame() const { return cur_frame_; }
    void setCurFrame(int frame) { cur_frame_ = frame % total_frame_; }
    int getTotalFrame() const { return total_frame_; }
    void setTotalFrame(int frame) { total_frame_ = frame; }
    int getFPS() const { return FPS; }
    void setFPS(int fps) { FPS = fps; }
    float getTimeCounter() const { return time_counter_; }
    void setTimeCounter(float time) { time_counter_ = time; }
    bool isLoop() const { return is_loop_; }
    void setLoop(bool loop) { is_loop_ = loop; }
};