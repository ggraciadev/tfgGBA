#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include <bn_sprite_ptr.h>
#include "GameObject.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "BoxCollision.h"
#include "bn_sprite_items_character.h"

#define COLLISION_OFFSET_X 0
#define COLLISION_OFFSET_Y 0
#define COLLISION_WIDTH 1
#define COLLISION_HEIGHT 1

#define JUMP_SPEED -5

class Character : public GameObject {
public:
    Character();
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);
    virtual ~Character();

protected:

    MovementComponent movement;
    InputComponent input;
    BoxCollision boxCollision;
    bn::optional<bn::sprite_ptr> sprite;
    

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void PhysicsUpdate() override;
    virtual void Render() override;

    virtual void SetMapCollision(MapCollision* mc);

    static Character* CreateCharacter();

    virtual void SetLayerDepth(int depth) override;
    virtual void SetZOrder(char z_order) override;

    void SetInputMovement(bn::fixed_point md) {movement.SetInputMovement(md);}
    void SetInputMovementX(bn::fixed x) {movement.SetInputMovementX(x);}
    void SetInputMovementY(bn::fixed y) {movement.SetInputMovementY(y);}

    void Jump();

};

#endif