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
    ClearMapGraphics();
    for(int i = 0; i < currentRoomIndex; ++i) {
        GenerateMapRoomInterior(&mapPtr->mapRooms[i]);
        GenerateMapRoomGraphics(&mapPtr->mapRooms[i], &mapPtr->mapLayer);
    }
    //mapPtr->GenerateMapGraphics();
    mapPtr->mapLayer.backLayerComponent.ReloadMap();
}

void MapGenerator::ClearMapGraphics() {
    for(int i = 0; i < REAL_MAP_HEIGHT; ++i) {
        for(int j = 0; j < REAL_MAP_WIDTH; ++j) {
            mapPtr->mapLayer.backLayerComponent.SetTileIndex(j, i, 0);
        }
    }
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
        mapCollisions->SetMapCollisionType(i, room->pos.y(), MapCollisionType::ROOM_EXTERIOR);
        for(int j = 1; j <= GROUND_MIN_HEIGHT; ++j) {
            mapCollisions->SetMapCollisionType(i, room->pos.y() + room->size.y() - j, MapCollisionType::COLLISION);
        }
    }
    for(int i = room->pos.y() + 1; i < room->pos.y() + room->size.y(); ++i) {
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
        room->downDoor = (bn::point(begin.x(), end.x()));
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

        room->SetCentralPlatformPos(bn::point(beginX, endY));
        room->SetCentralPlatoformSize(endX - beginX);
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

    room->upRoomPlatformPosTop = bn::point(initPos, begin.y());
    
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

    room->upRoomPlatformPosCenter = bn::point(initPos, begin.y());

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
                    
}

void MapGenerator::GenerateMapRoomGraphicsFirstCoat(MapRoom* room, MapLayer* mapLayer) {
    int initX = room->pos.x();
    int endX = initX + room->size.x();
    int initY = room->pos.y();
    int endY = initY + room->size.y();

    for(int i = initY ; i < endY + 1; ++i) {
        for(int j = initX; j < endX; ++j) {
            MapCollisionType currentCollision = mapLayer->mapCollision.GetCollisionByCell(j, i);
            MapCollisionType leftCollision = mapLayer->mapCollision.GetCollisionByCell(j-1, i);
            MapCollisionType rightCollision = mapLayer->mapCollision.GetCollisionByCell(j+1, i);
            MapCollisionType botCollision = mapLayer->mapCollision.GetCollisionByCell(j, i+1);
            MapCollisionType botLeftCollision = mapLayer->mapCollision.GetCollisionByCell(j-1, i+1);
            MapCollisionType botRightCollision = mapLayer->mapCollision.GetCollisionByCell(j+1, i+1);

            int tile = 0;
            
            if(currentCollision == MapCollisionType::COLLISION) {
                if(leftCollision == MapCollisionType::COLLISION && rightCollision == MapCollisionType::COLLISION) {
                    tile = 25 + j % 2;
                }
                else if(leftCollision == MapCollisionType::COLLISION) {
                    tile = 38 + j % 2;
                }
                else if(rightCollision == MapCollisionType::COLLISION) {
                    tile = 42 + j % 2;
                }
                else if(botLeftCollision == MapCollisionType::COLLISION) {
                    tile = 36 + j % 2;
                }
                else if(botRightCollision == MapCollisionType::COLLISION) {
                    tile = 40 + j % 2;
                }
                else if(j == initX){
                    tile = 45;
                }
                else if(j == endX - 1) {
                    tile = 44;
                }
            }
            else if(botCollision == MapCollisionType::COLLISION) {
                if(botLeftCollision == MapCollisionType::COLLISION && botRightCollision == MapCollisionType::COLLISION) {
                    tile = 23 + j % 2;
                }
                else if(botLeftCollision == MapCollisionType::COLLISION) {
                    tile = 36 + j % 2;
                }
                else if(botRightCollision == MapCollisionType::COLLISION) {
                    tile = 40 + j % 2;
                }
                else if(j == initX){
                    tile = 45;
                }
                else if(j == endX - 1) {
                    tile = 44;
                }
            }
            else if((i == endY || i == initY) && currentCollision == MapCollisionType::ROOM_EXTERIOR) {
                tile = 27;
            }
            else if(i != endY){
                tile = 1;
            }

            if(tile != 0) {
                mapLayer->backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, tile);
            }
        }
    }
}

void MapGenerator::GenerateMapRoomGraphicsPlatforms(MapRoom* room, MapLayer* mapLayer) {
    int initX = room->centralPlatformPos.x();
    int endX = initX + room->centralPlatformSize;
    int initY = room->centralPlatformPos.y() - 1;
    int endY = initY + 1;

    int tile = -1;

    for(int i = initY; i < endY; ++i) {
        for(int j = initX; j < endX; ++j) {
            
            tile = 30 + j%2;

            if(tile != -1){
                mapLayer->backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, tile);
            }
        }
    }

    initX = room->upRoomPlatformPosCenter.x();
    endX = initX + PLATFORM_MIN_WIDTH;

    for(int i = initX; i < endX; ++i) {
        tile = 30 + i%2;
        mapLayer->backLayerComponent.SetTileIndex(i + MAP_X_OFFSET, room->upRoomPlatformPosCenter.y() + MAP_Y_OFFSET, tile);
    }

    initX = room->upRoomPlatformPosTop.x();
    endX = initX + PLATFORM_MIN_WIDTH;

    for(int i = initX; i < endX; ++i) {
        tile = 30 + i%2;
        mapLayer->backLayerComponent.SetTileIndex(i + MAP_X_OFFSET, room->upRoomPlatformPosTop.y() + MAP_Y_OFFSET, tile);
    }

}

void MapGenerator::GenerateMapRoomGraphicsWindows(MapRoom* room, MapLayer* mapLayer) {
    GenerateMapRoomPlatformGraphicsWindows(room, mapLayer);
    GenerateMapRoomGroundGraphicsWindows(room, mapLayer);
    
}

void MapGenerator::GenerateMapRoomPlatformGraphicsWindows(MapRoom* room, MapLayer* mapLayer) {
    int initX = room->centralPlatformPos.x();
    int endX = initX + room->centralPlatformSize;
    int windowHeight = 5;
    int initY = room->centralPlatformPos.y() - windowHeight - 1;
    int endY = initY + windowHeight;
    
    for(int i = initY; i < endY; ++i) {
        int offset = 0;
        if(i == endY-1) {
            offset = 7;
        }
        for(int j = initX; j < endX; ++j) {
            int tile = -1;
            if(i == initY || i == endY-1) {
                if(j == initX) {
                    tile = 6 + offset;
                }
                else if(j == (endX - initX) / 2 + initX) {
                    tile = 8 + offset;
                }
                else if(j == endX-1) {
                    tile = 9 + offset;
                }
                else {
                    tile = 7 + offset;
                }
            }
            else {
                if(j == initX) {
                    tile = 10;
                }
                else if(j == endX - 1) {
                    tile = 12;
                }
                else if (j == (endX - initX) / 2 + initX) {
                    tile = 11;
                }
                else {
                    tile = 0;
                }
            }

            if(tile != -1) {
                mapLayer->backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, tile);
            }
        }
    }
}
void MapGenerator::GenerateMapRoomGroundGraphicsWindows(MapRoom* room, MapLayer* mapLayer) {
    MapRoom* downRoom = room->downRoom;
    int initX = room->pos.x() + 1;
    int endX = room->pos.x() + room->size.x() - 1;
    int initY = room->centralPlatformPos.y() + 1;
    int endY = room->pos.y() + room->size.y() -2;
    
    if(downRoom != nullptr) {
        initX = room->pos.x() + 1;
        endX = room->downDoor.x() - 1;
        initY = room->centralPlatformPos.y() + 1;
        endY = room->pos.y() + room->size.y() -2;
        
        GenerateBigWindowGraphic(initX, endX, initY, endY, mapLayer);

        initX = room->downDoor.y() + 1;
        endX = room->pos.x() + room->size.x() - 1;
        initY = room->centralPlatformPos.y() + 1;
        endY = room->pos.y() + room->size.y() -2;
        
        GenerateBigWindowGraphic(initX, endX, initY, endY, mapLayer);
    }
    else {
        int widndowWidth = 9;
        int first = initX;
        int last = endX;
        initX = first + 1;
        endX = first + widndowWidth;
        GenerateBigWindowGraphic(initX, endX, initY, endY, mapLayer);

        endX = last - 1;
        initX = endX - widndowWidth;
        GenerateBigWindowGraphic(initX, endX, initY, endY, mapLayer);
    }
    
}

void MapGenerator::GenerateBigWindowGraphic(int initX, int endX, int initY, int endY, MapLayer* mapLayer) {
    if(initX >= endX) {
        return;
    }
    for(int i = initY; i < endY; ++i) {
        for(int j = initX; j < endX; ++j) {
            int tile = -1;
            if(j == initX) {
                if(i == endY-2) {
                    tile = 17;
                }
                else if(i == endY-1) {
                    tile = 20;
                }
                else if(i == initY) {
                    tile = 6;
                }
                else {
                    tile = 10;
                }
            }
            else if(j == endX - 1) {
                if(i == endY-2) {
                    tile = 19;
                }
                else if(i == endY-1) {
                    tile = 22;
                }
                else if(i == initY) {
                    tile = 9;
                }
                else {
                    tile = 12;
                }
            }
            else if(j == (endX - initX) / 2 + initX && i < endY - 2){
                if(i == initY) {
                    tile = 8;
                }
                else {
                    tile = 11;
                }
            }
            else {
                if(i == endY-2) {
                    tile = 18;
                }
                else if(i == endY-1) {
                    tile = 21;
                }
                else if(i == initY) {
                    tile = 7;
                }
                else {
                    tile = 0;
                }
            }
            
            if(tile != -1) {
                mapLayer->backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, tile);
            }
        }
    }
}