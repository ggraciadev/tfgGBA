#ifndef BF_LAYER_H
#define BF_LAYER_H
#include "GameObjects/GameObject.h"
#include "GameObjectComponents/FollowComponent.h"
#include "GameObjectComponents/BackgroundLayerComponent.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

template <int CELLS_X, int CELLS_Y>
class Layer : public GameObject {
public:
    Layer();
    virtual ~Layer();

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
Layer<CELLS_X, CELLS_Y>::Layer() : GameObject::GameObject() {

    
}

template <int CELLS_X, int CELLS_Y>
Layer<CELLS_X, CELLS_Y>::~Layer() {

}

template <int CELLS_X, int CELLS_Y>
void Layer<CELLS_X, CELLS_Y>::Start(LayerType _layerType) {
    layerType = _layerType;
    followComponent.SetFollowObject(camera);
    backLayerComponent.SetLayerType(_layerType);
    AddComponent(&followComponent);
    AddComponent(&backLayerComponent);
    

    GameObject::Start();
}



template <int CELLS_X, int CELLS_Y>
void Layer<CELLS_X, CELLS_Y>::Update() {
    GameObject::Update();
}

template <int CELLS_X, int CELLS_Y>
void Layer<CELLS_X, CELLS_Y>::SetLayerDepth(int depth) {
    bn::fixed speed = 1;
    
    GameObject::SetLayerDepth(depth);
    if(layerDepth == -1) {
        speed = -1.0f;
    }
    else {
        speed = 1 - 1.0f/(layerDepth+1);
        SetZOrder(3);
    }
    followComponent.SetAlphaOffset(speed);
    backLayerComponent.SetLayerDepth(layerDepth);
    
}

template <int CELLS_X, int CELLS_Y>
char Layer<CELLS_X, CELLS_Y>::GetBackgroundLayer() {
    return layerDepth;
}

template <int CELLS_X, int CELLS_Y>
void Layer<CELLS_X, CELLS_Y>::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    backLayerComponent.SetZOrder(zOrder);
}

#endif