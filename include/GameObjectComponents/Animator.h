#ifndef BF_ANIMATOR_H
#define BF_ANIMATOR_H

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_sprite_item.h>

#define FRAME_SPEED 4

template <int MAX_SIZE_ANIM>
struct AnimInfo {

    char animationFrames[MAX_SIZE_ANIM];
    char animationLenght;
    bool looping;
    bool canReplay;

    AnimInfo() {
        animationLenght = 0;
        looping = true;
        canReplay = false;
    }

    AnimInfo(const char (& frames)[MAX_SIZE_ANIM], const char lenght, bool loop = false, bool replay = false) {
        for(int i = 0; i < lenght; ++i) {
            animationFrames[i] = frames[i];
        }
        animationLenght = lenght;
        looping = loop;
        canReplay = replay;
    }
};

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
class Animator : public GameObjectComponent {
public:
    
    Animator() = default;
    virtual ~Animator() = default;

protected:
    bool flipped;
    char currentFrame;
    char currentTime;
    char currentAnimation;

    AnimInfo<MAX_SIZE_ANIM> animations [NUM_ANIMATIONS];

    bn::optional<bn::sprite_ptr> sprite;
    bn::optional<bn::sprite_item> spriteItem;
public:
    virtual void SetSpriteItem(const bn::sprite_item& s);

    virtual void UpdateAnimation();
    virtual void UpdateAnimationTimer();
    virtual void SetCurrentAnimation(char anim, bool forceChange = false);

    virtual void Start() override;
    virtual void Update() override;

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    void SetFlipped(bool flip);
    inline bool GetFlipped() {return flipped;}

    void SetAnimations(const AnimInfo<MAX_SIZE_ANIM> (& anims)[NUM_ANIMATIONS]) {
        for(int i = 0; i < NUM_ANIMATIONS; ++i) animations[i] = anims[i];
    }
};

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::Start() {
    updateType = UpdateType::RENDER;
    GameObjectComponent::Start();
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::SetSpriteItem(const bn::sprite_item& s){ 
    spriteItem = s; 
    sprite = spriteItem->create_sprite(0, 0);
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::UpdateAnimation() {
    if(currentTime >= FRAME_SPEED) {
        int size = animations[currentAnimation].animationLenght - !animations[currentAnimation].looping;
        if(currentFrame < size) {
            currentFrame++;
            if(currentFrame >= size && animations[currentAnimation].looping) {
                currentFrame = 0;
            }
        }

    }
    sprite->set_tiles(spriteItem->tiles_item().create_tiles(animations[currentAnimation].animationFrames[currentFrame]));
    currentTime = 0;
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::UpdateAnimationTimer() {

}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::Update() {
    currentTime ++;
    if(currentTime >= FRAME_SPEED) {
        UpdateAnimation();
    }
    if(sprite.has_value()) {
        sprite->set_position(gameObject->GetScreenPosition());
    }
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::SetLayerDepth(int depth) {
    if(sprite.has_value()) {
        sprite->set_bg_priority(depth);
    }
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::SetZOrder(char z_order) {
    if(sprite.has_value()) {
        sprite->set_z_order(z_order);
    }
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::SetFlipped(bool flip) {
    sprite->set_horizontal_flip(flip);
    
}

template <int NUM_ANIMATIONS, int MAX_SIZE_ANIM>
void Animator<NUM_ANIMATIONS, MAX_SIZE_ANIM>::SetCurrentAnimation(char anim, bool forceChange) {
    if((animations[anim].canReplay && forceChange)|| anim != currentAnimation) {
        currentAnimation = anim;
        currentFrame = 0;
        currentTime = 0;
        sprite->set_tiles(spriteItem->tiles_item().create_tiles(animations[currentAnimation].animationFrames[currentFrame]));
    }
}

#endif