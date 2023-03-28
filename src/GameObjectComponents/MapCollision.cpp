#include "GameObjectComponents/MapCollision.h"
#include "GameObjects/GameObject.h"

MapCollision::MapCollision() : GameObjectComponent::GameObjectComponent() {
    
}

MapCollision::~MapCollision() {

}

void MapCollision::Start() {
    updateType = UpdateType::PHYSICS_UPDATE;
    const int begin = MAP_HEIGHT-10;
    const int end = MAP_HEIGHT;
    
    //gameObject->SetLocalPosition(15,0);
    // for(int i = 0; i < end; ++i) {
    //     for(int j = 0; j < MAP_WIDTH; ++j) {
    //         if(i >= begin || i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
    //             collisions[j + i * MAP_WIDTH].collision = COLLISION;
    //         }
    //         else {
    //             collisions[j + i * MAP_WIDTH].collision = NONE;
    //         }
    //     }
    // }
    GameObjectComponent::Start();
}

MapCollisionType MapCollision::GetCollisionByCell(int cellX, int cellY) const { 
    MapCollisionType result = MapCollisionType::COLLISION;
    if(cellX >= 0 && cellX < MAP_WIDTH && cellY >= 0 && cellY < MAP_HEIGHT) {
        result = (MapCollisionType)collisions[cellX + MAP_WIDTH * cellY].collision; 
    }
    return result;
}

void MapCollision::SetMapCollisionType(int cellX, int cellY, MapCollisionType collisionType) {
    if(cellX >= 0 && cellX < MAP_WIDTH && cellY >= 0 && cellY < MAP_HEIGHT) {
        collisions[cellX + MAP_WIDTH * cellY].collision = collisionType; 
    }
}
