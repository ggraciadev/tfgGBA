#ifndef BF_BACKGROUND_LAYER_COMPONENT_H
#define BF_BACKGROUND_LAYER_COMPONENT_H


#define EMPTY_TILE 0
#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_fixed_point.h>
#include <bn_regular_bg_item.h>
#include "bn_regular_bg_items_ground_b0.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_item.h>

enum LayerType {CITY_LAYER_0, CITY_LAYER_1, CITY_LAYER_2};

template <int CELLS_X, int CELLS_Y>
class BackgroundLayerComponent : public GameObjectComponent{
public:
    
    BackgroundLayerComponent();
    virtual ~BackgroundLayerComponent();



protected:

    alignas(int) bn::regular_bg_map_cell cells[CELLS_X * CELLS_Y];
    bn::optional<bn::regular_bg_map_item> map_item;
    bn::optional<bn::regular_bg_ptr> bg;
    bn::optional<bn::regular_bg_map_ptr> bg_map;

    bn::regular_bg_map_cell* temp_cell;
    bn::regular_bg_map_cell_info temp_cell_info;
    

public:
    virtual void Start();
    virtual void Update();

    void SetTileIndex(int cellX, int cellY, int tileIndex);
    inline void ReloadMap() { bg_map->reload_cells_ref(); }

    //inline void SetLayerType(LayerType _layerType) { layerType = _layerType; }

    inline virtual void SetLayerDepth(int depth) {
        if(bg.has_value()) {
            bg->set_priority(depth);
        }
    }
    inline virtual void SetZOrder(char z_order) {
        if(bg.has_value()) {
            bg->set_z_order(z_order);
        }
    }
};

template <int CELLS_X, int CELLS_Y>
BackgroundLayerComponent<CELLS_X, CELLS_Y>::BackgroundLayerComponent() : GameObjectComponent::GameObjectComponent() {
    map_item = bn::regular_bg_map_item (cells[0], bn::size(CELLS_X, CELLS_Y));

    bn::regular_bg_item bg_item (bn::regular_bg_items::ground_b0.tiles_item(), bn::regular_bg_items::ground_b0.palette_item(), *map_item);

    bg = bg_item.create_bg(0, 0);
    bg_map = bg->map();
}

template <int CELLS_X, int CELLS_Y>
BackgroundLayerComponent<CELLS_X, CELLS_Y>::~BackgroundLayerComponent() {

}

template <int CELLS_X, int CELLS_Y>
void BackgroundLayerComponent<CELLS_X, CELLS_Y>::SetTileIndex(int cellX, int cellY, int tileIndex) {
    if(cellX >= 0 && cellX < CELLS_X && cellY >= 0 && cellY < CELLS_Y) {
        
        temp_cell = &cells[map_item->cell_index(cellX, cellY)];
        temp_cell_info = bn::regular_bg_map_cell_info(*temp_cell);
        temp_cell_info.set_tile_index(tileIndex);
        *temp_cell = temp_cell_info.cell();
    }
}

template <int CELLS_X, int CELLS_Y>
void BackgroundLayerComponent<CELLS_X, CELLS_Y>::Start() {
    
}
    
template <int CELLS_X, int CELLS_Y>
void BackgroundLayerComponent<CELLS_X, CELLS_Y>::Update() {
    if(bg.has_value()) {
        bg->set_position(gameObject->GetScreenPosition());
    }
}


#endif