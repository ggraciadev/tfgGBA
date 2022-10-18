#include "Character.h"

Character::Character() {
    
}

Character::~Character() {

}

void Character::Start() {
    if(!sprite.has_value()) {
        sprite = bn::sprite_items::character.create_sprite(0, 0);
    }
    movement.SetCurrentMovementSpeed(1);
    input.SetMovementComponent(&movement);

    AddComponent(&movement);
    AddComponent(&input);


    GameObject::Start();
}

void Character::Update() {
    GameObject::Update();
}

void Character::Render() {
    GameObject::Render();
    sprite->set_position(GetScreenPosition());
}

void Character::SetLayerDepth(int depth) {
    SetZOrder(1);
    GameObject::SetLayerDepth(depth);
    sprite->set_bg_priority(layerDepth);
}

void Character::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    sprite->set_z_order(z_order);
}
