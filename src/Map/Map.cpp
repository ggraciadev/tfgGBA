#include "Map.h"
#include "Camera.h"
#include "bn_regular_bg_items_sky.h"
#include "bn_regular_bg_items_layer2.h"

void Map::Start() {
    mapLayer.SetLayerDepth(0);
    mapLayer.SetZOrder(5);
    mapLayer.SetLocalPosition(0,0);
    mapLayer.Start(LayerType::CITY_LAYER_0);

    skyLayer.SetBackgroundGraphic(bn::regular_bg_items::sky);
    skyLayer.SetLayerDepth(3);
    mapLayer.SetZOrder(5);
    skyLayer.Start();

    layer2.SetBackgroundGraphic(bn::regular_bg_items::layer2);
    layer2.SetLayerDepth(2);
    mapLayer.SetZOrder(5);
    layer2.Start();
}

void Map::SetCamera(Camera* cam) {
    mapLayer.SetCamera(cam);
    skyLayer.SetCamera(cam);
    layer2.SetCamera(cam);
}

void Map::GenerateMapGraphics() {
    
}

void Map::Update() {
    mapLayer.Update();
    skyLayer.Update();
    layer2.Update();
}

void Map::Render() {
    mapLayer.Render();
    skyLayer.Render();
    layer2.Render();
}