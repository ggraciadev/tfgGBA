#include "Layer.h"

#include <bn_regular_bg_item.h>

#include "bn_regular_bg_items_ground_b0.h"

Layer::Layer() : GameObject::GameObject() {
    layerDepth = 0;
}

Layer::~Layer() {

}

void Layer::Start() {
    GameObject::Start();

    map_item = bn::regular_bg_map_item (cells[0], bn::size(CELLS_X, CELLS_Y));

    bn::regular_bg_item bg_item (bn::regular_bg_items::ground_b0.tiles_item(), bn::regular_bg_items::ground_b0.palette_item(), *map_item);

    bg = bg_item.create_bg(0, 0);
    bg_map = bg->map();

    bn::regular_bg_map_cell* current_cell;

    int begin = START_Y_POSITION;
    int end = begin + LAYER_HEIGHT;

    for(int i = begin; i < end; ++i) {
        for(int j = 0; j < CELLS_X; ++j) {
            current_cell = &cells[map_item->cell_index(j, i)];
            bn::regular_bg_map_cell_info current_cell_info(*current_cell);
            if(i == begin) {
                current_cell_info.set_tile_index(j % (END_TOP_TILES - START_TOP_TILES) + START_TOP_TILES);
            }
            else if(i == end - 1) {
                current_cell_info.set_tile_index(j % (BLOCK_WIDTH) + START_BOT_TILES + BLOCK_WIDTH);
            }
            else if (i == end - 2) {
                current_cell_info.set_tile_index(j % (BLOCK_WIDTH) + START_BOT_TILES);
            }
            else {
                current_cell_info.set_tile_index(j % (BLOCK_WIDTH) + START_MID_TILES + (1+i) % 2);
            }

            *current_cell = current_cell_info.cell();
        }
    }
    bg_map->reload_cells_ref();
    bg->big();
}

void Layer::Update() {
    GameObject::Update();
    //AddLocalOffset(0, 1);
    //SetLocalPosition(camera->GetWorldPosition() * layerMovementAlpha);
}   

void Layer::Render() {
    GameObject::Render();
    if(bg.has_value()) {
        bg->set_position(GetScreenPosition());
    }
}

void Layer::SetLayerDepth(int depth) {
    layerDepth = depth;
    bn::fixed speed = 1;
    
    if(depth == -1) {
        depth = 0;
        if(back.has_value()) {
            back->set_z_order(0);
        }
        speed = -1.0f;
    }
    else {
        speed = 1 - 1.0f/(layerDepth+1);
    }
    if(back.has_value()) {
        back->set_priority(depth);
        back->set_z_order(3);
    }

    // int size = childList.size();
    // for(int i = 0; i < size; ++i) {
    //     childList[i]->SetLayerDepth(layerDepth);
    // }
    
    layerMovementAlpha = speed;
}

void Layer::SetBackground(bn::regular_bg_ptr b, int layer) {
    back = b;
    SetLayerDepth(layer);
}