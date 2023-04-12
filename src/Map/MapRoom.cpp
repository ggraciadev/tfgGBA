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

void MapRoom::GenerateRoomInterior(MapLayer& map, bn::random& rand) {
    GenerateMapCollisions(&map.mapCollision, rand);
}

void MapRoom::GenerateMapCollisions(MapCollision* mapCollisions, bn::random& rand) {
    GenerateRoomInteriorTiles(mapCollisions);
    GenerateRoomWalls(mapCollisions);
    GenerateRoomDoorsAndPlatforms(mapCollisions, rand);
    GenerateRoomInteriorWalls(mapCollisions, rand);
    
}



void MapRoom::GenerateRoomInteriorTiles(MapCollision* mapCollisions) {
    for (int i = pos.y() + CEIL_MIN_HEIGHT; i < pos.y() - GROUND_MIN_HEIGHT + size.y(); ++i) {
        for(int j = pos.x() + 1; j < pos.x() + size.x() - 1; j++) {
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::ROOM_INTERIOR);
        }
    }
}

void MapRoom::GenerateRoomWalls(MapCollision* mapCollisions) {
    for (int i = pos.x(); i < pos.x() + size.x(); i++) {
        mapCollisions->SetMapCollisionType(i, pos.y(), MapCollisionType::COLLISION);
        for(int j = 1; j <= GROUND_MIN_HEIGHT; ++j) {
            mapCollisions->SetMapCollisionType(i, pos.y() + size.y() - j, MapCollisionType::COLLISION);
        }
    }
    for(int i = pos.y(); i < pos.y() + size.y(); ++i) {
        mapCollisions->SetMapCollisionType(pos.x(), i, MapCollisionType::COLLISION);
        mapCollisions->SetMapCollisionType(pos.x() + size.x() - 1, i, MapCollisionType::COLLISION);
    }
}

void MapRoom::GenerateRoomInteriorWalls(MapCollision* mapCollisions, bn::random& rand) {
    if(size.x() > MIN_HORIZONTAL_SUBDIVISION) {
        int tempPos = pos.x() + size.x() / 2 + rand.get_int(-size.x() / 8, size.x() / 8 + 1);
        
        for(int i = pos.y() + 1; i < pos.y() + size.y() - 1; ++i) {
            for(int j = tempPos - HORIZONTAL_SUBDIVISION_WALL_WIDTH/2; j <= tempPos + HORIZONTAL_SUBDIVISION_WALL_WIDTH/2; ++j) {
                mapCollisions->SetMapCollisionType(j, i, MapCollisionType::COLLISION);
            }
        }

        int unionDoors = 1;//rand.get_int(1, Utils::Max(1, size.x() / MIN_HORIZONTAL_SUBDIVISION) + 1);

        for(int i = 0; i < unionDoors; ++i) {
            int beginPos = pos.y();
            int endPos = beginPos + ROOM_DOOR_SIZE;
            switch(rand.get_int(0, 4)) {
                case 0: //por arriba
                    beginPos = Utils::Clamp(pos.y() + 1, pos.y(), pos.y() + size.y()-1);
                    endPos = Utils::Clamp(beginPos + ROOM_DOOR_SIZE, pos.y(), pos.y() + size.y()-1);
                    break;
                default: //por el medio
                    beginPos = Utils::Clamp(pos.y() + size.y() / 2 - ROOM_DOOR_SIZE / 2, pos.y(), pos.y() + size.y()-1);
                    endPos = Utils::Clamp(beginPos + ROOM_DOOR_SIZE, pos.y(), pos.y() + size.y()-1);
                    break;
            }
            //HUECO DE LA PARED PARA PODER PASAR
            for(int j = beginPos; j < endPos; j++) {
                for(int k = tempPos - HORIZONTAL_SUBDIVISION_WALL_WIDTH/2; k <= tempPos + HORIZONTAL_SUBDIVISION_WALL_WIDTH; k++) {
                    mapCollisions->SetMapCollisionType(k, j, MapCollisionType::ROOM_INTERIOR);
                }
            }
            beginPos = Utils::Clamp(tempPos - rand.get_int(MIN_HORIZONTAL_BLOCK_PLATFORM, MAX_HORIZONTAL_BLOCK_PLATFORM), pos.x(), pos.x() + size.x()-1);
            int endX = Utils::Clamp(tempPos + rand.get_int(MIN_HORIZONTAL_BLOCK_PLATFORM, MAX_HORIZONTAL_BLOCK_PLATFORM), pos.x(), pos.x() + size.x()-1);
            //PLATAFORMA HORIZONTAL
            for(int j = beginPos; j < endX; j++) {
                mapCollisions->SetMapCollisionType(j, endPos, MapCollisionType::PLATFORM);
            }
        }
    }
}

void MapRoom::GenerateRoomDoorsAndPlatforms(MapCollision* mapCollisions, bn::random& rand) {
    bn::point begin;
    bn::point end;

    if(downRoom != nullptr) {
        begin.set_x(Utils::Max(pos.x(), downRoom->pos.x()) + 1);
        begin.set_y(pos.y() + size.y() - 1);
        end.set_x(Utils::Min(pos.x() + size.x(), downRoom->pos.x() + downRoom->size.x()) - 1);
        end.set_y(pos.y() + size.y());
        GenerateRoomDoor(begin, end, mapCollisions);
    }
    if(leftRoom != nullptr) {
        begin.set_x(pos.x());
        begin.set_y(Utils::Max(pos.y(), leftRoom->pos.y()) + CEIL_MIN_HEIGHT);
        end.set_x(pos.x()+1);
        end.set_y(Utils::Min(pos.y() + size.y(), leftRoom->pos.y() + leftRoom->size.y()) - GROUND_MIN_HEIGHT);
        GenerateRoomDoor(begin, end, mapCollisions);
        //GenerateRoomPlatforms(mapCollisions, begin, end, rand);
    }
    if(rightRoom != nullptr) {
        begin.set_x(pos.x() + size.x() - 1);
        begin.set_y(Utils::Max(pos.y(), rightRoom->pos.y()) + CEIL_MIN_HEIGHT);
        end.set_x(pos.x() + size.x());
        end.set_y(Utils::Min(pos.y() + size.y(), rightRoom->pos.y() + rightRoom->size.y()) - GROUND_MIN_HEIGHT);
        GenerateRoomDoor(begin, end, mapCollisions);
        //GenerateRoomPlatforms(mapCollisions, begin, end, rand);
    }
    if(upRoom != nullptr) {
        begin.set_x(Utils::Max(pos.x(), upRoom->pos.x()) + 1);
        begin.set_y(pos.y());
        end.set_x(Utils::Min(pos.x() + size.x(), upRoom->pos.x() + upRoom->size.x()) - 1);
        end.set_y(pos.y() + 1);
        GenerateRoomDoor(begin, end, mapCollisions);
        //GenerateRoomPlatforms(mapCollisions, begin, end, rand);
    }
}

void MapRoom::GenerateRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions) {
    for(int i = begin.y(); i < end.y(); ++i) {
        for(int j = begin.x(); j < end.x(); ++j) {
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::ROOM_INTERIOR);
        }
    }
}

void MapRoom::GenerateRoomPlatforms(MapCollision* mapCollisions, bn::point otherRoomGroundBegin, bn::point otherRoomGroundEnd, bn::random& rand) {
    int currentDirection = Utils::GetSign(pos.x() - otherRoomGroundBegin.x());
    int initPosX = otherRoomGroundBegin.x() + currentDirection * PLAYER_JUMP_WIDTH;
    int destinyPosX;
    if(currentDirection > 0) {
        destinyPosX = pos.x() + size.x();
    }
    else {
        destinyPosX = pos.x();
    }
    int lastPlatformX;
    int platformLenght;
    int i = otherRoomGroundEnd.y();

    while(i < pos.y() + size.y() - 1) {
        platformLenght = rand.get_int(PLATFORM_MIN_WIDTH, PLATFORM_MAX_WIDTH);
        destinyPosX = Utils::Clamp(initPosX + platformLenght * currentDirection, pos.x() + 1, pos.x() + size.x() - 1);
        
        for(int j = initPosX; j != destinyPosX; j += currentDirection) {
            if(currentDirection > 0 && j >= destinyPosX || currentDirection < 0 && j <= destinyPosX) {
                break;
            }
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::PLATFORM);
        }
        i += PLAYER_JUMP_HEIGHT;
        initPosX += PLAYER_JUMP_WIDTH * currentDirection;
        if(initPosX >= pos.x() + size.x() -1 || initPosX <= pos.x() + 1) {
            currentDirection *= -1;
            initPosX -= PLAYER_JUMP_WIDTH * currentDirection * 2;
        }
    }
}
