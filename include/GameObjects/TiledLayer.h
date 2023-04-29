#ifndef BF_TILED_LAYER_H
#define BF_TILED_LAYER_H
#include "GameObjects/GameObject.h"
#include "GameObjectComponents/FollowComponent.h"
#include "GameObjectComponents/BackgroundLayerComponent.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

template <int CELLS_X, int CELLS_Y>
class TiledLayer : public GameObject {
public:
    TiledLayer();
    virtual ~TiledLayer();

protected:

    LayerType layerType;

    FollowComponent followComponent;
    BackgroundLayerComponent<CELLS_X, CELLS_Y> backLayerComponent;
    //bn::fixed layerMovementAlpha;


public:

    void Start(LayerType _layerType);
    void Update();

    char GetBackgroundLayer();
    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);
};

template <int CELLS_X, int CELLS_Y>
TiledLayer<CELLS_X, CELLS_Y>::TiledLayer() : GameObject::GameObject() {

    
}

template <int CELLS_X, int CELLS_Y>
TiledLayer<CELLS_X, CELLS_Y>::~TiledLayer() {

}

template <int CELLS_X, int CELLS_Y>
void TiledLayer<CELLS_X, CELLS_Y>::Start(LayerType _layerType) {
    layerType = _layerType;
    followComponent.SetFollowObject(camera);
    backLayerComponent.SetLayerType(_layerType);
    AddComponent(&followComponent);
    AddComponent(&backLayerComponent);
    

    GameObject::Start();
}



template <int CELLS_X, int CELLS_Y>
void TiledLayer<CELLS_X, CELLS_Y>::Update() {
    GameObject::Update();
}

template <int CELLS_X, int CELLS_Y>
void TiledLayer<CELLS_X, CELLS_Y>::SetLayerDepth(int depth) {
    bn::fixed speed = 1;
    
    GameObject::SetLayerDepth(depth);
    if(layerDepth == -1) {
        speed = -1.0f;
    }
    else if(layerDepth == 0) {
        speed = 0;
    }
    else {
        speed = 1 - 1.0f/((1+layerDepth)*2);
        SetZOrder(3);
    }
    followComponent.SetAlphaOffset(speed);
    backLayerComponent.SetLayerDepth(layerDepth);
    
}

template <int CELLS_X, int CELLS_Y>
char TiledLayer<CELLS_X, CELLS_Y>::GetBackgroundLayer() {
    return layerDepth;
}

template <int CELLS_X, int CELLS_Y>
void TiledLayer<CELLS_X, CELLS_Y>::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    backLayerComponent.SetZOrder(zOrder);
}

#endif