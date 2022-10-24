#include "MapLayer.h"

MapLayer::MapLayer() : Layer<MAP_WIDTH,MAP_HEIGHT>::Layer(){

}

MapLayer::~MapLayer() {

}


void MapLayer::Start(LayerType _layerType) {
    AddComponent(&mapCollision);
    Layer::Start(_layerType);

    // GameObject::Start();
    // layerType = _layerType;

    // bn::regular_bg_map_cell* current_cell;

    // for(int i = 0; i < MAP_HEIGHT; ++i) {
    //     for(int j = 0; j < MAP_WIDTH; ++j) {
    //         current_cell = &cells[map_item->cell_index(j, i)];
    //         bn::regular_bg_map_cell_info current_cell_info(*current_cell);
    //         current_cell_info.set_tile_index(mapCollision.GetCollisionByCell(j, i));
    //         *current_cell = current_cell_info.cell();
    //     }
    // }
    // bg_map->reload_cells_ref();
}