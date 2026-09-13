#include "sprite.h"
#include "../core/game.h"
#include "../core/assetStore.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::getInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteComponent(ObjectScreen *parent, const std::string &file_path, float scale, AnchorType anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setParent(parent);
    sprite->setTexture(Texture(file_path));
    sprite->normalizeOffsetToAnchor(anchor);
    sprite->setScale(scale);
    parent->addChild(sprite);
    return sprite;
}

void Sprite::setTexture(Texture texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}

void Sprite::render()
{
    if (!texture_.texture || !parent_ || is_finish_) return;
    
    Game::getInstance().renderTexture(texture_, parent_->getScreenPosition() + offset_, size_);
}
