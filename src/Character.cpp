#include "Character.h"

Character::Character() {
    sprite = bn::sprite_items::character.create_sprite(0, 0);
    
}

Character::~Character() {

}

void Character::Start() {
    GameObject::Start();
    movement.SetGameObject(this);
    movement.SetCurrentMovementSpeed(1);
    movement.SetInputMovementX(1);
}

void Character::Update() {
    GameObject::Update();
    movement.Update();
}

void Character::Render() {
    GameObject::Render();
    sprite->set_position(GetScreenPosition());
}
