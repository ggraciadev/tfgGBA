#ifndef BF_MAP_GENERATOR_H
#define BF_MAP_GENERATOR_H

#include "Map.h"
#include "bn_optional.h"
#include "bn_random.h"

enum RoomGenerationState {NOT_CREATED, CREATED, EXPANDED, CANT_EXPAND };

class MapGenerator {
public:
    MapGenerator() = default;
    ~MapGenerator() = default;
    
    void GenerateMap(Map* map, unsigned seed);

protected:
    int currentStep;
    int currentRoomIndex;
    Map* mapPtr;
    bn::random rand;
    RoomGenerationState roomState [MAX_MAP_ROOMS];

    void InitMapGenerator(Map* map);
    bool GenerateMapStep();
    bn::point GenerateRoomSize(int width = 0, int height = 0);
    MapRoom* GenerateMapRoom(bn::point size, bn::point beginSearch, bn::point endSearch);
    bn::optional<bn::point> GetValidRoomPosition(bn::point roomSize, bn::point beginSearch, bn::point endSearch);
    MapRoom* GenerateMapRoomAt(bn::point position, bn::point size);
    bool GenerateAdjacentRooms(int roomIndex);

    void GenerateMapRoomInterior(MapRoom* room, bool bossRoom = false);

    //Para hacer los bordes de la sala
    void GenerateMapRoomInteriorTiles(MapRoom* room, MapCollision* mapCollisions);
    //Para hacer los bordes de la sala
    void GenerateMapRoomWalls(MapRoom* room, MapCollision* mapCollisions);
    //Para hacer las connexiones entre salas
    void GenerateMapRoomDoors(MapRoom* room, MapCollision* mapCollisions, bn::random& rand);

    void GenerateMapRoomPlatforms(MapRoom* room, MapCollision* mapCollisions, bn::random& rand);
    void GenerateUpMapRoomPlatform(MapRoom* room, MapCollision* mapCollisions, bn::random& rand);
    
    //Para hacer las connexiones entre salas
    void GenerateMapRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions);

    void ClearMapGraphics();

    void GenerateMapRoomGraphics(MapRoom* room, MapLayer* mapLayer);
    void GenerateMapRoomGraphicsFirstCoat(MapRoom* room, MapLayer* mapLayer);
    void GenerateMapRoomGraphicsPlatforms(MapRoom* room, MapLayer* mapLayer);
    void GenerateMapRoomGraphicsWindows(MapRoom* room, MapLayer* mapLayer);
    void GenerateMapRoomDoorGraphic(MapRoom* room,  MapLayer* mapLayer);

    void GenerateMapRoomPlatformGraphicsWindows(MapRoom* room, MapLayer* mapLayer);
    void GenerateMapRoomGroundGraphicsWindows(MapRoom* room, MapLayer* mapLayer);

    void GenerateBigWindowGraphic(int initX, int endX, int initY, int endY, MapLayer* mapLayer);

public:
    
};

#endif