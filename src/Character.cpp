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
