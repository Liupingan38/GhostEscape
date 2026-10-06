#include "effect.h"
#include "../core/scene.h"

Effect *Effect::addEffectChild(Object *parent, const std::string &path, ObjectWorld *nextObj, const glm::vec2& position,float scale)
{
    Effect* effect = new Effect();
    effect->init();
    effect->start_anim_= SpriteAnim::addSpriteAnimComponent(effect,path);
    effect->start_anim_->setLoop(false);
    effect->start_anim_->setScale(scale);
    effect->setPosition(position);
    effect->finish_obj_ = nextObj;
    //if(nextObj) effect->finish_obj_->setPosition(position);
    if(parent) parent->addChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);

    // 每帧检测动画是否播完，播放后生成物体，并加入场景
    checkAnimIsFinish();
}

void Effect::checkAnimIsFinish()
{
    if (isPendingKill() || !start_anim_ || !start_anim_->isFinish()) return;

    if (finish_obj_) {
        game_.getCurrentScene()->addChildSafe(finish_obj_);
        finish_obj_ = nullptr; // 已交给场景，避免重复入队
    }

    setPendingKill(true); // 标记整个特效，下一帧由父对象统一清理
}
