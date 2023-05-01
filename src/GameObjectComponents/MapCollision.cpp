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
    for(int i = 0; i < end; ++i) {
        for(int j = 0; j < MAP_WIDTH; ++j) {
            collisions[j + i * MAP_WIDTH].collision = MapCollisionType::ROOM_EXTERIOR;
        }
    }
    GameObjectComponent::Start();
}

MapCollisionType MapCollision::GetCollisionByCell(int cellX, int cellY) const { 
    MapCollisionType result = MapCollisionType::ROOM_EXTERIOR;
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
