#include "sprite.h"
#include "../core/game.h"
#include "../core/assetStore.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::getInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

void Sprite::setTexture(Texture texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}

void Sprite::render()
{
    if (!texture_.texture)
    {
        SDL_Log("Sprite::render: texture is null");
        return;
    }
    if(!parent_)
    {
        SDL_Log("Sprite::render: parent is null");
        return;
    }
    Game::getInstance().renderTexture(texture_, parent_->getScreenPosition() + offset_, size_);
}
