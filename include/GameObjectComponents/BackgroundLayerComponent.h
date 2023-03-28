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

    LayerType layerType;

    const char START_Y_POSITION [3] = {54,16,12};
    const char LAYER_HEIGHT [3] = {8, 10, 10};

    const char BLOCK_WIDTH [3] = {3,2,2};

    const char START_TOP_TILES [3] = {1,16,22};
    const char END_TOP_TILES [3] = {3,17,23};

    const char START_MID_TILES [3] = {4,18,24};
    const char END_MID_TILES [3] = {9,21,25};

    const char LOOP_MID_QUANTITY_TILES [3] = {2,1,2};

    const char START_BOT_TILES [3] = {10,18,26};
    const char END_BOT_TILES [3] = {12,21,26};
    const char BOT_LOOP_TILES [3] = {13,18,26};
    const char END_BOT_LOOP_TILES [3] = {15,21,26};

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

    inline void SetLayerType(LayerType _layerType) { layerType = _layerType; }

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
    if(layerType == 0) return;
    bn::regular_bg_map_cell* current_cell;

    const int begin = START_Y_POSITION[(int)layerType];
    const int end = begin + LAYER_HEIGHT[(int)layerType];

    const int startTopTiles = START_TOP_TILES[(int)layerType];
    const int endTopTiles = END_TOP_TILES[(int)layerType];

    const int startMidTiles = START_MID_TILES[(int)layerType];
    const int endMidTiles = END_MID_TILES[(int)layerType];
    const int loopMidTilesNum = LOOP_MID_QUANTITY_TILES[(int)layerType];

    const int startBotTiles = START_BOT_TILES[(int)layerType];
    const int endBotTiles = END_BOT_TILES[(int)layerType];
    const int botLoopStartTile = BOT_LOOP_TILES[(int)layerType];
    const int botLoopEndTile = END_BOT_LOOP_TILES[(int)layerType];

    const int blockWidth = BLOCK_WIDTH[(int)layerType];
    const int blockTopHeight = (endTopTiles - startTopTiles) / blockWidth + 1;
    const int blockMidHeight = (endMidTiles - startMidTiles) / blockWidth + 1;
    
    const int blockBotHeight = (endBotTiles - startBotTiles) / blockWidth + 1;
    const int blockBotLoopHeight = (botLoopEndTile - botLoopStartTile) / blockWidth + 1;
    

    for(int i = begin; i < end; ++i) {
        for(int j = 0; j < CELLS_X; ++j) {
            current_cell = &cells[map_item->cell_index(j, i)];
            bn::regular_bg_map_cell_info current_cell_info(*current_cell);

            if(i - begin < blockTopHeight) {
                current_cell_info.set_tile_index(j % (blockWidth) + startTopTiles + blockWidth * ((i - begin) % blockTopHeight));
                //current_cell_info.set_tile_index(2);
            }
            else if(i - begin < blockTopHeight + loopMidTilesNum) {
                current_cell_info.set_tile_index(j % (blockWidth) + startMidTiles + blockWidth * ((i - begin - blockTopHeight) % blockMidHeight));
            }
            else if(i == begin + blockTopHeight + loopMidTilesNum) {
                current_cell_info.set_tile_index(j % (blockWidth) + startBotTiles + blockWidth * ((i - begin - blockTopHeight - loopMidTilesNum) % blockBotHeight));
            }
            else {
                current_cell_info.set_tile_index(j % (blockWidth) + botLoopStartTile + blockWidth * ((end - i) % blockBotLoopHeight));
            }

            *current_cell = current_cell_info.cell();
        }
    }
    bg_map->reload_cells_ref();
}
    
template <int CELLS_X, int CELLS_Y>
void BackgroundLayerComponent<CELLS_X, CELLS_Y>::Update() {
    if(bg.has_value()) {
        bg->set_position(gameObject->GetScreenPosition());
    }
}


#endif