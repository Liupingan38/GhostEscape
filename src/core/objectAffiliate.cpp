#include "objectAffiliate.h"

void ObjectAffiliate::normalizeOffsetToAnchor(AnchorType anchor)
{
    switch (anchor)
    {
    case AnchorType::ANCHOR_TOP_LEFT:
        offset_ = glm::vec2(0.f, 0.f);
        break;
    case AnchorType::ANCHOR_TOP_CENTER:
        offset_ = glm::vec2(-size_.x / 2.f, 0.f);
        break;
    case AnchorType::ANCHOR_TOP_RIGHT:
        offset_ = glm::vec2(-size_.x, 0.f);
        break;
    case AnchorType::ANCHOR_CENTER_LEFT:
        offset_ = glm::vec2(0.f, -size_.y / 2.f);
        break;
    case AnchorType::ANCHOR_CENTER:
        offset_ = glm::vec2(-size_.x / 2.f, -size_.y / 2.f);
        break;
    case AnchorType::ANCHOR_CENTER_RIGHT:
        offset_ = glm::vec2(-size_.x, -size_.y / 2.f);
        break;
    case AnchorType::ANCHOR_BOTTOM_LEFT:
        offset_ = glm::vec2(0.f, -size_.y);
        break;
    case AnchorType::ANCHOR_BOTTOM_CENTER:
        offset_ = glm::vec2(-size_.x / 2.f, -size_.y);
        break;
    case AnchorType::ANCHOR_BOTTOM_RIGHT:
        offset_ = glm::vec2(-size_.x, -size_.y);
        break;
    default:
        break;
    }
    anchor_ = anchor;
}

void ObjectAffiliate::setScale(float scale)
{
    size_ *= scale;
    normalizeOffsetToAnchor(anchor_);
}

void ObjectAffiliate::setSize(const glm::vec2 &size)
{
    size_ = size;
    normalizeOffsetToAnchor(anchor_);
}
