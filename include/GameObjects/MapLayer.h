#ifndef BF_MAP_LAYER_H
#define BF_MAP_LAYER_H

#include "GameObjects/Layer.h"
#include "GameObjectComponents/MapCollision.h"

class MapLayer : public Layer <REAL_MAP_WIDTH, REAL_MAP_HEIGHT> {

friend class MapRoom;
friend class MapGenerator;
friend class Map;

public:
    MapLayer();
    virtual ~MapLayer();

protected:
    MapCollision mapCollision;
    

public:
    void Start(LayerType _layerType);

    MapCollision* GetMapCollision() { return &mapCollision; }
    

};

#endif