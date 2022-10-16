#include "Player.h"

Player::Player() : Entity::Entity() {

}

Player::Player(const int posX, const int posY, GameObject* _parent, const bn::fixed gravity) : Entity::Entity(posX, posY, _parent, gravity){
    
}

Player::~Player() {

}