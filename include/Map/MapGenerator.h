#ifndef BF_MAP_GENERATOR_H
#define BF_MAP_GENERATOR_H

#include "Map.h"
#include "bn_optional.h"
#include "bn_random.h"

#define ROOM_MIN_SIZE 24
#define ROOM_MAX_SIZE 48
#define ROOM_DOOR_SIZE 18

enum RoomGenerationState {NOT_CREATED, CREATED, EXPANDED, CANT_EXPAND };

class MapGenerator {
public:
    MapGenerator() = default;
    ~MapGenerator() = default;
    
    void InitMapGenerator(Map* map);
    void GenerateMap();

protected:
    int currentStep;
    int currentRoomIndex;
    Map* mapPtr;
    bn::random rand;
    RoomGenerationState roomState [MAX_MAP_ROOMS];

    bool GenerateMapStep();
    bn::point GenerateRoomSize(int width = 0, int height = 0);
    MapRoom* GenerateMapRoom(bn::point size, bn::point beginSearch, bn::point endSearch);
    bn::optional<bn::point> GetValidRoomPosition(bn::point roomSize, bn::point beginSearch, bn::point endSearch);
    MapRoom* GenerateMapRoomAt(bn::point position, bn::point size);
    bool GenerateAdjacentRooms(int roomIndex);
};

#endif