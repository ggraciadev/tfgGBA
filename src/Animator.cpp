#include "Animator.h"
#include "GameObject.h"

Animator::Animator() : GameObjectComponent::GameObjectComponent() {

}

Animator::~Animator() {

}

void Animator::Start() {
    updateType = UpdateType::RENDER;
    GameObjectComponent::Start();
}

void Animator::SetSpriteItem(const bn::sprite_item& s){ 
    spriteItem = s; 
    sprite = spriteItem->create_sprite(0, 0);
}

void Animator::UpdateAnimation() {
    if(currentTime >= FRAME_SPEED) {
        currentFrame = (currentFrame + 1) % animationsLenght[currentAnimation];
    }
    sprite->set_tiles(spriteItem->tiles_item().create_tiles(animations[currentAnimation][currentFrame]));
    currentTime = 0;
}

void Animator::UpdateAnimationTimer() {

}

void Animator::Update() {
    currentTime ++;
    if(currentTime >= FRAME_SPEED) {
        UpdateAnimation();
    }
    if(sprite.has_value()) {
        sprite->set_position(gameObject->GetScreenPosition());
    }
}

void Animator::SetLayerDepth(int depth) {
    if(sprite.has_value()) {
        sprite->set_bg_priority(depth);
    }
}

void Animator::SetZOrder(char z_order) {
    if(sprite.has_value()) {
        sprite->set_z_order(z_order);
    }
}

void Animator::SetFlipped(bool flip) {
    sprite->set_horizontal_flip(flip);
    
}

void Animator::SetCurrentAnimation(char anim) {
    if(anim != currentAnimation) {
        currentAnimation = anim;
        currentFrame = 0;
        currentTime = 0;
        //sprite->set_tiles(spriteItem->tiles_item().create_tiles(animations[currentAnimation][currentFrame]));
    }
}