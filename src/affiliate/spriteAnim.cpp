#include "spriteAnim.h"

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale, bool bCentered, int fps)
{
    auto spriteAnim = new SpriteAnim();
    spriteAnim->init();
    spriteAnim->setParent(parent);
    parent->addChild(spriteAnim);
    spriteAnim->setTexture(Texture(file_path));
    spriteAnim->setScale(scale); // 缩小精灵
    if (bCentered)
    {
        spriteAnim->setOffset(glm::vec2(-spriteAnim->getSize().x / 2.f, -spriteAnim->getSize().y / 2.f));
    }
    spriteAnim->FPS = fps;

    return spriteAnim;
}

void SpriteAnim::update(float dt)
{
    if (is_finish_) return;
    time_counter_ += dt;
    if (time_counter_ >= 1.0f / FPS)
    {
        cur_frame_ = (cur_frame_ + 1) % total_frame_;
        if (cur_frame_ == 0)
        {
            if (!is_loop_)
            {
                is_finish_ = true;
                return;
            }
        }
        time_counter_ = 0.0f;
    }
    texture_.src_rect.x = static_cast<float>(cur_frame_) * texture_.src_rect.h;
}

void SpriteAnim::setTexture(Texture texture)
{
    texture_ = texture;
    total_frame_ = static_cast<int>(texture_.src_rect.w / texture_.src_rect.h);
    texture_.src_rect.w = texture_.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
