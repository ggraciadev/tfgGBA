#include "Character.h"
#include "MapCollision.h"

Character::Character() {
    
}

Character::~Character() {

}

void Character::Start() {
    if(!sprite.has_value()) {
        sprite = bn::sprite_items::character.create_sprite(0, 0);
    }
    movement.SetCurrentMovementSpeed(1);
    input.SetCharacter(this);
    boxCollision.Setup(COLLISION_OFFSET_X, COLLISION_OFFSET_Y, COLLISION_WIDTH, COLLISION_HEIGHT);

    AddComponent(&movement);
    AddComponent(&input);
    AddComponent(&boxCollision);

    GameObject::Start();
}

void Character::SetMapCollision(MapCollision* mc) {
    boxCollision.SetMapCollision(mc);
}

void Character::Update() {
    GameObject::Update();
}

void Character::PhysicsUpdate() {
    GameObject::PhysicsUpdate();
    boxCollision.PhysicsUpdate();
    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
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

void Character::Jump() {
    movement.AddImpulse(0, JUMP_SPEED);
}
