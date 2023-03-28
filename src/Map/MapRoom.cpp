#include "MapRoom.h"
#include "GameObjects/MapLayer.h"
#include "utils.h"

void MapRoom::InitRoom() {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = bn::point(-1,-1);
    size = bn::point(-1,-1);
}

void MapRoom::InitRoom(bn::point _size) {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = bn::point(-1,-1);
    size = _size;
}

void MapRoom::InitRoom(bn::point _pos, bn::point _size) {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = _pos;
    size = _size;
}

void MapRoom::GenerateRoomInterior(MapLayer& map) {
    GenerateMapCollisions(&map.mapCollision);
    GenerateRoomTiles(map);
}

void MapRoom::GenerateMapCollisions(MapCollision* mapCollisions) {
    GenerateRoomWalls(mapCollisions);
    GenerateRoomDoors(mapCollisions);
    GenerateRoomPlatforms(mapCollisions);
}

void MapRoom::GenerateRoomWalls(MapCollision* mapCollisions) {
    for (int i = pos.x(); i < pos.x() + size.x(); i++) {
        mapCollisions->SetMapCollisionType(i, pos.y(), MapCollisionType::COLLISION);
        mapCollisions->SetMapCollisionType(i, pos.y() + size.y() - 1, MapCollisionType::COLLISION);
    }
    for(int i = pos.y(); i < pos.y() + size.y(); ++i) {
        mapCollisions->SetMapCollisionType(pos.x(), i, MapCollisionType::COLLISION);
        mapCollisions->SetMapCollisionType(pos.x() + size.x() - 1, i, MapCollisionType::COLLISION);
    }
}

void MapRoom::GenerateRoomDoors(MapCollision* mapCollisions) {
    return;
    bn::point begin;
    bn::point end;

    if(leftRoom != nullptr) {
        begin.set_x(pos.x());
        begin.set_y(Utils::Max(pos.y(), leftRoom->pos.y()));
        end.set_x(pos.x());
        end.set_y(Utils::Min(pos.y() + size.y()-1, leftRoom->pos.y() + leftRoom->size.y() -1));
        GenerateRoomDoor(begin, end, mapCollisions);
    }
    if(rightRoom != nullptr) {
        begin.set_x(pos.x() + size.x() - 1);
        begin.set_y(Utils::Max(pos.y(), leftRoom->pos.y()));
        end.set_x(pos.x() + size.x() - 1);
        end.set_y(Utils::Min(pos.y() + size.y(), leftRoom->pos.y() + leftRoom->size.y()));
        GenerateRoomDoor(begin, end, mapCollisions);
    }
    if(upRoom != nullptr) {
        begin.set_x(Utils::Max(pos.x(), leftRoom->pos.x()));
        begin.set_y(pos.y());
        end.set_x(Utils::Min(pos.x(), leftRoom->pos.x()));
        end.set_y(pos.y());
        GenerateRoomDoor(begin, end, mapCollisions);
    }
    if(downRoom != nullptr) {
        begin.set_x(Utils::Max(pos.x(), leftRoom->pos.x()));
        begin.set_y(pos.y() + size.y() - 1);
        end.set_x(Utils::Min(pos.x(), leftRoom->pos.x()));
        end.set_y(pos.y() + size.y() - 1);
        GenerateRoomDoor(begin, end, mapCollisions);
    }
}

void MapRoom::GenerateRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions) {
    for(int i = begin.y(); i < end.y(); ++i) {
        for(int j = begin.x(); j < end.x(); ++j) {
            mapCollisions->SetMapCollisionType(i, j, MapCollisionType::NONE);
        }
    }
}

void MapRoom::GenerateRoomPlatforms(MapCollision* mapCollisions) {

}

void MapRoom::GenerateRoomTiles(MapLayer& map) {
    // = nullptr;
    int initY = pos.y();
    int initX = pos.x();
    int endY = initY + size.y();
    int endX = initX + size.x();
    for (int i = initY; i < endY; i++) {
        for(int j = initX; j < endX; ++j) {
            //map.backLayerComponent.SetTileIndex(j, i, 5);
            switch(map.mapCollision.GetCollisionByCell(j, i)) {
                case MapCollisionType::NONE:
                    map.backLayerComponent.SetTileIndex(j, i, 0);
                    break;
                case MapCollisionType::COLLISION:
                    map.backLayerComponent.SetTileIndex(j, i, 4);
                    break;
                case MapCollisionType::PLATFORM:
                    break;
            }
        }
    }
}