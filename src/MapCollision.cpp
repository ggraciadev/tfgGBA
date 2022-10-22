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
    for(int i = 0; i < end; ++i) {
        for(int j = 0; j < MAP_WIDTH; ++j) {
            if(i >= begin || i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
                collisions[j + i * MAP_WIDTH] = COLLISION;
            }
            else {
                collisions[j + i * MAP_WIDTH] = NONE;
            }
        }
    }
    GameObjectComponent::Start();
}

void MapCollision::Update() {

}

MapCollisionType MapCollision::GetCollisionByCell(int cellX, int cellY) { 
    MapCollisionType result = MapCollisionType::NONE;
    if(cellX >= 0 && cellX < MAP_WIDTH && cellY >= 0 && cellY < MAP_HEIGHT) {
        result = collisions[cellX + MAP_WIDTH * cellY]; 
    }
    return result;
    // return collisions[cellX + MAP_WIDTH * cellY];
}
