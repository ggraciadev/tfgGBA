#ifndef BF_ANIMATOR_H
#define BF_ANIMATOR_H

#include "GameObjectComponent.h"
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>

#define FRAME_SPEED 4
#define SPRITE_SHEET_INCLUDE "bn_sprite_items_character.h"
#include SPRITE_SHEET_INCLUDE
#define SPRITE_SHEET bn::sprite_items::character

class Animator : public GameObjectComponent {
public:
    
    Animator();
    virtual ~Animator();

protected:
    bool flipped;
    char currentFrame;
    char currentTime;
    char currentAnimation;

    char animations[2][16] = {{0,1,2,3,4,5,6}, {7,8,9,10,11,12,13,14,15,16,12}};
    char animationsLenght[2] = {7,11};

    bn::optional<bn::sprite_ptr> sprite;
public:

    virtual void UpdateAnimation();
    virtual void UpdateAnimationTimer();
    virtual void SetCurrentAnimation(char anim);

    virtual void Start() override;
    virtual void Render() override;

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    void SetFlipped(bool flip);
    bool GetFlipped() {return flipped;}
};

#endif