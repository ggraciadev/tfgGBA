#ifndef BF_MAP_LAYER_H
#define BF_MAP_LAYER_H

#include "Layer.h"
#include "MapCollision.h"

class MapLayer : public Layer <MAP_WIDTH, MAP_HEIGHT> {

public:
    MapLayer();
    virtual ~MapLayer();

protected:
    MapCollision mapCollision;
    

public:
    virtual void Start(LayerType _layerType) override;

    MapCollision* GetMapCollision() { return &mapCollision; }
    

};

#endif