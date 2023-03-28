#ifndef BF_MAP_LAYER_H
#define BF_MAP_LAYER_H

#include "GameObjects/Layer.h"
#include "GameObjectComponents/MapCollision.h"

class MapLayer : public Layer <MAP_WIDTH, MAP_HEIGHT> {

friend class MapRoom;
friend class MapGenerator;

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