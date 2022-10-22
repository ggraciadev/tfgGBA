#include "MapCollision.h"
#include "GameObject.h"

MapCollision::MapCollision() : GameObjectComponent::GameObjectComponent() {
    
}

MapCollision::~MapCollision() {

}

void MapCollision::Start() {
    const int begin = 20;
    const int end = MAP_HEIGHT;
    
    gameObject->SetLocalPosition(15,0);
    for(int i = begin; i < end; ++i) {
        for(int j = 0; j < MAP_WIDTH; ++j) {
            collisions[j + i * MAP_WIDTH] = COLLISION;
        }
    }
    for(int i = 0; i < end; ++i) {
        for(int j = 0; j < MAP_WIDTH; ++j) {
            if(i < begin) {
                collisions[j + i * MAP_WIDTH] = NONE;
            }
            else {
                collisions[j + i * MAP_WIDTH] = COLLISION;
            }
        }
    }
    GameObjectComponent::Start();
}

void MapCollision::Update() {

}