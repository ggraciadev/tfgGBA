#include "Entity.h"

Entity::Entity() : Pawn::Pawn() {

}

Entity::Entity(const int posX, const int posY, GameObject* _parent, const bn::fixed gravity) : Pawn::Pawn(posX, posY, _parent, gravity){
    
}

Entity::~Entity() {

}