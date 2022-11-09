#ifndef BF_ANIMATOR_H
#define BF_ANIMATOR_H

#include "GameObjectComponent.h"
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_sprite_item.h>

#define FRAME_SPEED 4

class Animator : public GameObjectComponent {
public:
    
    Animator();
    virtual ~Animator();

protected:
    bool flipped;
    char currentFrame;
    char currentTime;
    char currentAnimation;

    char animations[2][16] = {{0,0,1,1,2,2,3,3,4,4,5,5,6,6}, {7,8,9,10,11,12,13,14,15,16,12}};
    char animationsLenght[2] = {14,11};

    bn::optional<bn::sprite_ptr> sprite;
    bn::optional<bn::sprite_item> spriteItem;
public:
    virtual void SetSpriteItem(const bn::sprite_item& s);

    virtual void UpdateAnimation();
    virtual void UpdateAnimationTimer();
    virtual void SetCurrentAnimation(char anim);

    virtual void Start() override;
    virtual void Update() override;

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    void SetFlipped(bool flip);
    bool GetFlipped() {return flipped;}
};

#endif