#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include <bn_sprite_ptr.h>
#include "GameObject.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "bn_sprite_items_character.h"

class Character : public GameObject {
public:
    Character();
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);
    virtual ~Character();

protected:

    MovementComponent movement;
    InputComponent input;
    bn::optional<bn::sprite_ptr> sprite;
    

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    static Character* CreateCharacter();

    virtual void SetLayerDepth(int depth) override;
    virtual void SetZOrder(char z_order) override;

};

#endif