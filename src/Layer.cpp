// #include "Layer.h"

// #include <bn_regular_bg_item.h>

// #include "bn_regular_bg_items_ground_b0.h"

// template <int CELLS_X, int CELLS_Y>
// Layer<CELLS_X, CELLS_Y>::Layer() : GameObject::GameObject() {

//     map_item = bn::regular_bg_map_item (cells[0], bn::size(CELLS_X, CELLS_Y));

//     bn::regular_bg_item bg_item (bn::regular_bg_items::ground_b0.tiles_item(), bn::regular_bg_items::ground_b0.palette_item(), *map_item);

//     bg = bg_item.create_bg(0, 0);
//     bg_map = bg->map();
// }

// template <int CELLS_X, int CELLS_Y>
// Layer<CELLS_X, CELLS_Y>::~Layer() {

// }

// template <int CELLS_X, int CELLS_Y>
// void Layer<CELLS_X, CELLS_Y>::Start(LayerType _layerType) {
//     layerType = _layerType;

//     GameObject::Start();

//     bn::regular_bg_map_cell* current_cell;

//     const int begin = START_Y_POSITION[(int)layerType];
//     const int end = begin + LAYER_HEIGHT[(int)layerType];


//     const int startTopTiles = START_TOP_TILES[(int)layerType];
//     const int endTopTiles = END_TOP_TILES[(int)layerType];
//     const int startMidTiles = START_MID_TILES[(int)layerType];
//     const int endMidTiles = END_MID_TILES[(int)layerType];
//     const int startBotTiles = START_BOT_TILES[(int)layerType];
//     const int endBotTiles = END_BOT_TILES[(int)layerType];

//     const int blockWidth = BLOCK_WIDTH[(int)layerType];
//     const int blockTopHeight = (endTopTiles - startTopTiles) / blockWidth + 1;
//     const int blockMidHeight = (endMidTiles - startMidTiles) / blockWidth + 1;
//     const int blockBotHeight = (endBotTiles - startBotTiles) / blockWidth + 1;


//     for(int i = begin; i < end; ++i) {
//         for(int j = 0; j < CELLS_X; ++j) {
//             current_cell = &cells[map_item->cell_index(j, i)];
//             bn::regular_bg_map_cell_info current_cell_info(*current_cell);
//             if(i < blockTopHeight) {
//                 current_cell_info.set_tile_index(j % (blockWidth) + startTopTiles + (blockTopHeight+i) % 2);
//             }
//             else if(i == end - blockTopHeight) {
//                 current_cell_info.set_tile_index(j % (blockWidth) + startBotTiles + (blockBotHeight+i) % 2);
//             }
//             else {
//                 current_cell_info.set_tile_index(j % (blockWidth) + startMidTiles + (blockMidHeight+i) % 2);
//             }

//             *current_cell = current_cell_info.cell();
//         }
//     }
//     bg_map->reload_cells_ref();
//     bg->big();
// }

// template <int CELLS_X, int CELLS_Y>
// void Layer<CELLS_X, CELLS_Y>::Update() {
//     GameObject::Update();
//     if(camera != nullptr) {
//         SetLocalPosition(camera->GetWorldPosition() * layerMovementAlpha);
//     }
// }   

// template <int CELLS_X, int CELLS_Y>
// void Layer<CELLS_X, CELLS_Y>::Render() {
//     GameObject::Render();
//     if(bg.has_value()) {
//         bg->set_position(GetScreenPosition());
//     }
// }

// template <int CELLS_X, int CELLS_Y>
// void Layer<CELLS_X, CELLS_Y>::SetLayerDepth(int depth) {
//     bn::fixed speed = 1;
    
//     GameObject::SetLayerDepth(depth);
//     if(layerDepth == -1) {
//         speed = -1.0f;
//     }
//     else {
//         speed = 1 - 1.0f/(layerDepth+1);
//         SetZOrder(3);
//     }
//     layerMovementAlpha = speed;
//     if(bg.has_value()) {
//         bg->set_priority(layerDepth);
//     }
// }

// template <int CELLS_X, int CELLS_Y>
// char Layer<CELLS_X, CELLS_Y>::GetBackgroundLayer() {
//     return layerDepth;
// }

// template <int CELLS_X, int CELLS_Y>
// void Layer<CELLS_X, CELLS_Y>::SetZOrder(char z_order) {
//     GameObject::SetZOrder(z_order);
//     if(bg.has_value()) {
//         bg->set_z_order(z_order);
//     }
// }