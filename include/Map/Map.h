#ifndef BF_MAP_H
#define BF_MAP_H

#include "MapRoom.h"
#include "MapLayer.h"

#define MAX_MAP_ROOMS 32

class Map {

    friend class MapGenerator;
    friend class Scene;

public:
    Map() = default;
    ~Map() = default;

protected:
    MapRoom mapRooms[MAX_MAP_ROOMS];
    MapLayer mapLayer;
};

#endif