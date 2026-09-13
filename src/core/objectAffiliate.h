#pragma once

#include "objectScreen.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen* parent_ = nullptr; // 父对象指针
    glm::vec2 offset_ = glm::vec2(0.f, 0.f); // 相对于锚点的偏移量
    glm::vec2 size_ = glm::vec2(1.f, 1.f); 
    AnchorType anchor_ = AnchorType::ANCHOR_CENTER; // 锚点类型

public:
    void normalizeOffsetToAnchor(AnchorType anchor); // 将偏移量归一化到锚点位置

    void setScale(float scale);

    // getter and setter
    ObjectScreen* getParent() const { return parent_; }
    void setParent(ObjectScreen* parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2& offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2& size);
    AnchorType getAnchor() const { return anchor_; }
    void setAnchor(AnchorType anchor) { anchor_ = anchor; }

};

    