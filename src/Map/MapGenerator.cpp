#include "MapGenerator.h"
#include "utils.h"

#define EXPAND_X_PROB 100
#define EXPAND_Y_PROB 33

bool MapGenerator::GenerateMapStep() {
    bool result = false;

    if(currentStep == 0) {
        bn::point roomSize = GenerateRoomSize();
        bn::point beginSearch(MAP_WIDTH / 2, MAP_HEIGHT / 2);
        bn::point endSearch(beginSearch.x() + ROOM_MAX_SIZE, beginSearch.y() + ROOM_MAX_SIZE);

        result = GenerateMapRoom(roomSize, beginSearch, endSearch) != nullptr;
    }
    else {
        int stepMax = currentRoomIndex;
        for(int i = currentStep-1; i < stepMax && i < MAX_MAP_ROOMS; ++i) {
            if(roomState[i] == RoomGenerationState::CREATED) {
                result = GenerateAdjacentRooms(i) || result;
            }
        }
    }
    if(currentRoomIndex >= MAX_MAP_ROOMS) {
        result = false;
    }
    currentStep++;
    return result;
}

bool MapGenerator::GenerateAdjacentRooms(int roomIndex) {
    bool result = false;
    MapRoom* tempMapRoom = &mapPtr->mapRooms[roomIndex];
    bn::point roomSize;
    bn::point beginSearch;
    bn::point endSearch;
    
    if(tempMapRoom->leftRoom == nullptr && rand.get_int(0,100) < EXPAND_X_PROB) {
        roomSize = GenerateRoomSize();
        beginSearch = bn::point(Utils::Clamp(tempMapRoom->pos.x()-1, 0, MAP_WIDTH), Utils::Clamp(tempMapRoom->pos.y() - roomSize.y() + ROOM_DOOR_SIZE, 0, MAP_HEIGHT));
        endSearch = bn::point(Utils::Clamp(beginSearch.x() - roomSize.x(), 0, MAP_WIDTH), Utils::Clamp(beginSearch.y() + roomSize.y() + tempMapRoom->size.y() - ROOM_DOOR_SIZE, 0, MAP_HEIGHT));
        
        MapRoom* tmpRoom = GenerateMapRoom(roomSize, beginSearch, endSearch);
        if(tmpRoom != nullptr) {
            tempMapRoom->leftRoom = tmpRoom;
            tmpRoom->rightRoom = tempMapRoom;
            result = true;
            roomState[roomIndex] = RoomGenerationState::EXPANDED;
        }
    }

    if(tempMapRoom->rightRoom == nullptr && rand.get_int(0,100) < EXPAND_X_PROB) {
        roomSize = GenerateRoomSize();
        beginSearch = bn::point(Utils::Clamp(tempMapRoom->pos.x() + tempMapRoom->size.x(), 0, MAP_WIDTH), Utils::Clamp(tempMapRoom->pos.y() - roomSize.y() + ROOM_DOOR_SIZE, 0, MAP_HEIGHT));
        endSearch = bn::point(Utils::Clamp(beginSearch.x() + roomSize.x() + 1, 0, MAP_WIDTH), Utils::Clamp(beginSearch.y() + roomSize.y() + tempMapRoom->size.y() - ROOM_DOOR_SIZE, 0, MAP_HEIGHT));
        
        MapRoom* tmpRoom = GenerateMapRoom(roomSize, beginSearch, endSearch);
        if(tmpRoom != nullptr) {
            tempMapRoom->rightRoom = tmpRoom;
            tmpRoom->leftRoom = tempMapRoom;
            result = true;
            roomState[roomIndex] = RoomGenerationState::EXPANDED;
        }
    }

    if(tempMapRoom->downRoom == nullptr && rand.get_int(0,100) < EXPAND_Y_PROB) {
        roomSize = GenerateRoomSize();

        beginSearch = bn::point(Utils::Clamp(tempMapRoom->pos.x() - roomSize.x() + ROOM_DOOR_SIZE, 0, MAP_WIDTH), Utils::Clamp(tempMapRoom->pos.y() + tempMapRoom->size.y(), 0, MAP_HEIGHT));
        endSearch = bn::point(Utils::Clamp(beginSearch.x() + roomSize.x() + tempMapRoom->size.x() - ROOM_DOOR_SIZE, 0, MAP_WIDTH), Utils::Clamp(beginSearch.y() + roomSize.y() + 1, 0, MAP_HEIGHT));
        MapRoom* tmpRoom = GenerateMapRoom(roomSize, beginSearch, endSearch);
        if(tmpRoom != nullptr) {
            tempMapRoom->downRoom = tmpRoom;
            tmpRoom->upRoom = tempMapRoom;
            result = true;
            roomState[roomIndex] = RoomGenerationState::EXPANDED;
        }
    }

    if(tempMapRoom->upRoom == nullptr && rand.get_int(0,100) < EXPAND_Y_PROB) {
        roomSize = GenerateRoomSize();

        beginSearch = bn::point(Utils::Clamp(tempMapRoom->pos.x() - roomSize.x() + ROOM_DOOR_SIZE, 0, MAP_WIDTH), Utils::Clamp(tempMapRoom->pos.y()-1, 0, MAP_HEIGHT));
        endSearch = bn::point(Utils::Clamp(beginSearch.x() + roomSize.x() + tempMapRoom->size.x() - ROOM_DOOR_SIZE, 0, MAP_WIDTH), Utils::Clamp(beginSearch.y() - roomSize.y(), 0, MAP_HEIGHT));
        
        MapRoom* tmpRoom = GenerateMapRoom(roomSize, beginSearch, endSearch);
        if(tmpRoom != nullptr) {
            tempMapRoom->upRoom = tmpRoom;
            tmpRoom->downRoom = tempMapRoom;
            result = true;
            roomState[roomIndex] = RoomGenerationState::EXPANDED;
        }
    }

    if(roomState[roomIndex] == RoomGenerationState::CREATED) {
        roomState[roomIndex] = RoomGenerationState::CANT_EXPAND;
        result = false;
    } 
    
    return result;
}

MapRoom* MapGenerator::GenerateMapRoom(bn::point size, bn::point beginSearch, bn::point endSearch) {
    MapRoom* result = nullptr;
    if(currentRoomIndex >= MAX_MAP_ROOMS) return nullptr;
    bn::optional<bn::point> roomPosition = GetValidRoomPosition(size, beginSearch, endSearch);
    if(roomPosition.has_value()) {
        result = GenerateMapRoomAt(*roomPosition, size);
    }
    
    return result;
}

bn::point MapGenerator::GenerateRoomSize(int width, int height) {
    bn::point result;
    if(height > 0) {
        result.set_y(height);
    }
    else {
        result.set_y(rand.get_int(ROOM_MIN_SIZE, ROOM_MAX_SIZE));
    }
    if(width > 0) {
        result.set_x(width);
    }
    else {
        result.set_x(rand.get_int(ROOM_MIN_SIZE, ROOM_MAX_SIZE));
    }

    return result;
}

bn::optional<bn::point>  MapGenerator::GetValidRoomPosition(bn::point roomSize, bn::point beginSearch, bn::point endSearch) {
    bn::optional<bn::point> result;
    result.reset();
    bn::point tempPos(-1,-1);
    bn::point direction(Utils::GetSign(endSearch.x() - beginSearch.x()), Utils::GetSign(endSearch.y() - beginSearch.y()));

    int widthCheck = 0;
    int heightCheck = 0;
    
    for(int i = beginSearch.y(); i != endSearch.y(); i += direction.y()) {
        widthCheck = 0;
        for(int j = beginSearch.x(); j != endSearch.x(); j += direction.x()) {
            if(mapPtr->mapLayer.GetMapCollision()->GetCollisionByCell(j, i) == MapCollisionType::COLLISION) {
                widthCheck = 0;
                heightCheck = -1; //como despues se suma uno, se quedara en 0
                break;
            }
            else {
                widthCheck++;
                if(widthCheck >= roomSize.x()) {
                    if (direction.x() > 0) {
                        tempPos.set_x(j - (roomSize.x() - 1));
                    }
                    else {
                        tempPos.set_x(j);
                    }
                    widthCheck = 0;
                    break;
                }
            }
        }
        heightCheck++;
        if(heightCheck >= roomSize.y()) {
            if (direction.y() > 0) {
                tempPos.set_y(i - (roomSize.y() - 1));
            }
            else {
                tempPos.set_y(i);
            }
            break;
        }
    }

    if(tempPos.x() != -1 && tempPos.y() != -1 ) {
        result = tempPos;
    }

    return result;
}

MapRoom* MapGenerator::GenerateMapRoomAt(bn::point position, bn::point size) {
    MapRoom* result = &mapPtr->mapRooms[currentRoomIndex];
    result->InitRoom(position, size);
    GenerateMapRoomWalls(result, &mapPtr->mapLayer.mapCollision);
    roomState[currentRoomIndex] = RoomGenerationState::CREATED;
    currentRoomIndex++;
    return result;
}

void MapGenerator::GenerateMap(unsigned seed) {
    bool finished = false;
    int temp = 2 * MAX_MAP_ROOMS;
    rand.set_seed(seed);
    //temp = 3;
    while(!finished) {
        if(temp-- <= 0) break;
        finished = currentRoomIndex >= MAX_MAP_ROOMS || !GenerateMapStep();
    }
    for(int i = 0; i < currentRoomIndex; ++i) {
        GenerateMapRoomInterior(&mapPtr->mapRooms[i]);
        GenerateMapRoomGraphics(&mapPtr->mapRooms[i], &mapPtr->mapLayer);
    }
    mapPtr->GenerateMapGraphics();
    //mapPtr->mapLayer.backLayerComponent.ReloadMap();
}


void MapGenerator::InitMapGenerator(Map* map) {
    mapPtr = map;
    currentStep = 0;
    currentRoomIndex = 0;
    for(int i = 0; i < MAX_MAP_ROOMS; ++i) {
        mapPtr->mapRooms[i].InitRoom();
        roomState[i] = RoomGenerationState::NOT_CREATED;
    }
}


 void MapGenerator::GenerateMapRoomInterior(MapRoom* room) {
    GenerateMapRoomInteriorTiles(room, &mapPtr->mapLayer.mapCollision);
    GenerateMapRoomWalls(room, &mapPtr->mapLayer.mapCollision);
    GenerateMapRoomDoors(room, &mapPtr->mapLayer.mapCollision, rand);
    GenerateMapRoomPlatforms(room, &mapPtr->mapLayer.mapCollision, rand);
 }

void MapGenerator::GenerateMapRoomInteriorTiles(MapRoom* room, MapCollision* mapCollisions) {
    for (int i = room->pos.y() + CEIL_MIN_HEIGHT; i < room->pos.y() - GROUND_MIN_HEIGHT + room->size.y(); ++i) {
        for(int j = room->pos.x() + 1; j < room->pos.x() + room->size.x() - 1; j++) {
            if(mapCollisions->GetCollisionByCell(j,i) != MapCollisionType::PLATFORM) {
                mapCollisions->SetMapCollisionType(j, i, MapCollisionType::ROOM_INTERIOR);
            }
        }
    }
}

void MapGenerator::GenerateMapRoomWalls(MapRoom* room, MapCollision* mapCollisions) {
    for (int i = room->pos.x(); i < room->pos.x() + room->size.x(); i++) {
        mapCollisions->SetMapCollisionType(i, room->pos.y(), MapCollisionType::COLLISION);
        for(int j = 1; j <= GROUND_MIN_HEIGHT; ++j) {
            mapCollisions->SetMapCollisionType(i, room->pos.y() + room->size.y() - j, MapCollisionType::COLLISION);
        }
    }
    for(int i = room->pos.y(); i < room->pos.y() + room->size.y(); ++i) {
        mapCollisions->SetMapCollisionType(room->pos.x(), i, MapCollisionType::COLLISION);
        mapCollisions->SetMapCollisionType(room->pos.x() + room->size.x() - 1, i, MapCollisionType::COLLISION);
    }
}

void MapGenerator::GenerateMapRoomDoors(MapRoom* room, MapCollision* mapCollisions, bn::random& rand) {
    bn::point begin;
    bn::point end;
    MapRoom* tempRoom;

    if(room->downRoom != nullptr) {
        tempRoom = room->downRoom;
        begin.set_x(Utils::Max(room->pos.x(), tempRoom->pos.x()) + 1);
        begin.set_y(room->pos.y() + room->size.y() - 1);
        end.set_x(Utils::Min(room->pos.x() + room->size.x(), tempRoom->pos.x() + tempRoom->size.x()) - 1);
        end.set_y(room->pos.y() + room->size.y());
        GenerateMapRoomDoor(begin, end, mapCollisions);
    }
    if(room->leftRoom != nullptr) {
        tempRoom = room->leftRoom;
        begin.set_x(room->pos.x());
        begin.set_y(Utils::Max(room->pos.y(), tempRoom->pos.y()) + CEIL_MIN_HEIGHT);
        end.set_x(room->pos.x()+1);
        end.set_y(Utils::Min(room->pos.y() + room->size.y(), tempRoom->pos.y() + tempRoom->size.y()) - GROUND_MIN_HEIGHT);
        GenerateMapRoomDoor(begin, end, mapCollisions);
    }
    if(room->rightRoom != nullptr) {
        tempRoom = room->rightRoom;
        begin.set_x(room->pos.x() + room->size.x() - 1);
        begin.set_y(Utils::Max(room->pos.y(), tempRoom->pos.y()) + CEIL_MIN_HEIGHT);
        end.set_x(room->pos.x() + room->size.x());
        end.set_y(Utils::Min(room->pos.y() + room->size.y(), tempRoom->pos.y() + tempRoom->size.y()) - GROUND_MIN_HEIGHT);
        GenerateMapRoomDoor(begin, end, mapCollisions);
    }
    if(room->upRoom != nullptr) {
        tempRoom = room->upRoom;
        begin.set_x(Utils::Max(room->pos.x(), tempRoom->pos.x()) + 1);
        begin.set_y(room->pos.y());
        end.set_x(Utils::Min(room->pos.x() + room->size.x(), tempRoom->pos.x() + tempRoom->size.x()) - 1);
        end.set_y(room->pos.y() + 1);
        GenerateMapRoomDoor(begin, end, mapCollisions);
    }
}

void MapGenerator::GenerateMapRoomPlatforms(MapRoom* room, MapCollision* mapCollisions, bn::random& rand) {
    if(room->size.x() > MIN_HORIZONTAL_SUBDIVISION) {
        int tempPos = room->pos.x() + room->size.x() / 2 + rand.get_int(-room->size.x() / 8, room->size.x() / 8 + 1);

       
        int beginX = Utils::Clamp(tempPos - rand.get_int(MIN_HORIZONTAL_BLOCK_PLATFORM, MAX_HORIZONTAL_BLOCK_PLATFORM), room->pos.x() + HORIZONTAL_SUBDIVISION_OFFSET, room->pos.x() + room->size.x()-1-HORIZONTAL_SUBDIVISION_OFFSET);
        int endX = Utils::Clamp(tempPos + rand.get_int(MIN_HORIZONTAL_BLOCK_PLATFORM, MAX_HORIZONTAL_BLOCK_PLATFORM), room->pos.x() + HORIZONTAL_SUBDIVISION_OFFSET, room->pos.x() + room->size.x()-1-HORIZONTAL_SUBDIVISION_OFFSET);
        int endY = room->pos.y() + room->size.y() - 1 - PLAYER_JUMP_HEIGHT * 2;
        
        for(int j = endY - HORIZONTAL_SUBDIVISION_GROUND_HEIGHT / 2; j < endY + HORIZONTAL_SUBDIVISION_GROUND_HEIGHT / 2; ++j) {
            for(int k = beginX; k < endX; k++) {
                mapCollisions->SetMapCollisionType(k, j, MapCollisionType::PLATFORM);
            }
        }
    }

    if(room->upRoom != nullptr) {
        GenerateUpMapRoomPlatform(room, mapCollisions, rand);
    }
}

void MapGenerator::GenerateUpMapRoomPlatform(MapRoom* room, MapCollision* mapCollisions, bn::random& rand) {
    int platformSize = MIN_HORIZONTAL_BLOCK_PLATFORM;

    bn::point begin;
    bn::point end;

    begin.set_x(Utils::Max(room->pos.x(), room->upRoom->pos.x()) + 1);
    begin.set_y(room->pos.y());
    end.set_x(Utils::Min(room->pos.x() + room->size.x(), room->upRoom->pos.x() + room->upRoom->size.x()) - 1);
    end.set_y(begin.y() + HORIZONTAL_SUBDIVISION_GROUND_HEIGHT);

    int initPos = room->upRoom->pos.x() + 1;
    int endPos = initPos + platformSize;

    if(room->pos.x() > room->upRoom->pos.x()) {
        initPos = end.x() - platformSize;
        endPos = end.x();
    }
    else {
        initPos = begin.x();
        endPos = begin.x() + platformSize;
    }

    
    for(int i = begin.y(); i < end.y(); ++i) {
        for(int j = initPos; j < endPos; ++j) {
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::PLATFORM);
        }
    }

    if(end.x() - begin.x() <= PLAYER_JUMP_WIDTH * 2) {
        if(room->pos.x() > room->upRoom->pos.x()) {
            initPos = begin.x();
            endPos = begin.x() + platformSize;
        }
        else {
            initPos = end.x() - platformSize;
            endPos = end.x();
        }
    }
    
    begin.set_y(begin.y() + PLAYER_JUMP_HEIGHT * 2);
    end.set_y(begin.y() + HORIZONTAL_SUBDIVISION_GROUND_HEIGHT);

    for(int i = begin.y(); i < end.y(); ++i) {
        for(int j = initPos; j < endPos; ++j) {
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::PLATFORM);
        }
    }
}
    
void MapGenerator::GenerateMapRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions) {
    for(int i = begin.y(); i < end.y(); ++i) {
        for(int j = begin.x(); j < end.x(); ++j) {
            mapCollisions->SetMapCollisionType(j, i, MapCollisionType::ROOM_INTERIOR);
        }
    }
}

void MapGenerator::GenerateMapRoomGraphics(MapRoom* room, MapLayer* mapLayer) {
    GenerateMapRoomGraphicsFirstCoat(room, mapLayer);
    GenerateMapRoomGraphicsPlatforms(room, mapLayer);
    GenerateMapRoomGraphicsWindows(room, mapLayer);
    //mapLayer.mapCollision.GetCollisionByCell(j, i)

    //mapLayer->backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, 0);
                    
}

void MapGenerator::GenerateMapRoomGraphicsFirstCoat(MapRoom* room, MapLayer* mapLayer) {
    int initX = room->pos.x();
    int endX = initX + room->size.x();
    int initY = room->pos.x();
    int endY = initY + room->pos.y();

    for(int i = initY; i < endY; ++i) {
        for(int j = initX; j < endX; ++j) {
            
        }
    }
}

void MapGenerator::GenerateMapRoomGraphicsPlatforms(MapRoom* room, MapLayer* mapLayer) {

}

void MapGenerator::GenerateMapRoomGraphicsWindows(MapRoom* room, MapLayer* mapLayer) {

}