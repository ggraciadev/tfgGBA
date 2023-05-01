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

MapRoom* Map::GetRoomByPosition(bn::fixed_point position) {
    for(int i = 0; i < MAX_MAP_ROOMS; ++i) {
        bn::point pos = mapRooms[i].GetPosition();
        bn::point size = mapRooms[i].GetSize();
        if(position.x() < pos.x() + size.x() && position.x() >= pos.x() &&
            position.y() < pos.y() + size.y() && position.y() > pos.y()) {
            
            return &mapRooms[i];
        }
    }

    return nullptr;
}

MapRoom* Map::GetBossRoom() {
    for(int i = 0; i < MAX_MAP_ROOMS; ++i) {
        if(mapRooms[i].IsBossRoom()) {
            return &mapRooms[i];
        }
    }

    return nullptr;
}