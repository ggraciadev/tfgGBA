#ifndef BF_MAP_H
#define BF_MAP_H

#include "MapRoom.h"
#include "MapLayer.h"

#define MAX_MAP_ROOMS 16

class Map {

    friend class MapGenerator;
    friend class Scene;

public:
    Map() = default;
    ~Map() = default;

    void GenerateMapGraphics();

protected:
    MapRoom mapRooms[MAX_MAP_ROOMS];
    //bool mapTilesOccupied[MAP_WIDTH * MAP_HEIGHT];
    MapLayer mapLayer;
};

#endif