#ifndef BF_MAP_H
#define BF_MAP_H

#include "MapRoom.h"
#include "MapLayer.h"
#include "BasicLayer.h"


#define MAX_MAP_ROOMS 24

class Camera;

class Map {

    friend class MapGenerator;
    friend class GameScene;

public:
    Map() = default;
    ~Map() = default;

    void GenerateMapGraphics();
    void Start();
    void Update();
    void Render();

    void SetCamera(Camera* cam);

protected:
    MapRoom mapRooms[MAX_MAP_ROOMS];
    //bool mapTilesOccupied[MAP_WIDTH * MAP_HEIGHT];
    MapLayer mapLayer;
    BasicLayer skyLayer;
    BasicLayer layer2;
};

#endif