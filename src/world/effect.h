#pragma once
#include "../core/objectWorld.h"
#include "../affiliate/spriteAnim.h"
#include <string>

class Effect : public ObjectWorld
{
protected:
    SpriteAnim* start_anim_ = nullptr; 
    ObjectWorld* finish_obj_ = nullptr;
    
public:
    static Effect* addEffectChild(Object* parent, const std::string& path, ObjectWorld* nextObj, const glm::vec2& position, float scale = 1.0f);
    virtual void update(float dt) override;

    // getter & setter
    SpriteAnim* getStartAnim() const { return start_anim_;}
    void setStartAnim(SpriteAnim* anim) { start_anim_ = anim;}
    ObjectWorld* getFinishObj() const { return finish_obj_;}
    void setFinishObj(ObjectWorld* obj) {finish_obj_ = obj;}

private:
    void checkAnimIsFinish();

};