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
    result->GenerateRoomWalls(&mapPtr->mapLayer.mapCollision);
    roomState[currentRoomIndex] = RoomGenerationState::CREATED;
    currentRoomIndex++;
    return result;
}

void MapGenerator::GenerateMap() {
    bool finished = false;
    int temp = 2 * MAX_MAP_ROOMS;
    //temp = 3;
    while(!finished) {
        if(temp-- <= 0) break;
        finished = currentRoomIndex >= MAX_MAP_ROOMS || !GenerateMapStep();
    }
    for(int i = 0; i < currentRoomIndex; ++i) {
        mapPtr->mapRooms[i].GenerateRoomInterior(mapPtr->mapLayer);
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