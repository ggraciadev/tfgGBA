#include "GameObject.h"

GameObject::GameObject() {
    relativePosition = bn::fixed_point(0,0);
}

GameObject::GameObject(int posX, int posY) {
    relativePosition = bn::fixed_point(posX,  posY);
}

GameObject::~GameObject() {

}