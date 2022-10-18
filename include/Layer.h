#ifndef BF_LAYER_H
#define BF_LAYER_H

#include "GameObject.h"


#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_item.h>

#define CELLS_X 64
#define CELLS_Y 32
#define CELLS_COUNT CELLS_X * CELLS_Y

#define LAYER_HEIGHT 6
#define START_Y_POSITION 20

#define BLOCK_WIDTH 3
#define EMPTY_TILE 0
#define START_TOP_TILES 1
#define END_TOP_TILES 3
#define START_MID_TILES 4
#define END_MID_TILES 9
#define START_BOT_TILES 10
#define END_BOT_TILES 15



class Layer : public GameObject {
public:
    Layer();
    virtual ~Layer();

protected:

    bn::fixed layerMovementAlpha;

    alignas(int) bn::regular_bg_map_cell cells[CELLS_COUNT];
    bn::optional<bn::regular_bg_map_item> map_item;
    bn::optional<bn::regular_bg_ptr> bg;
    bn::optional<bn::regular_bg_map_ptr> bg_map;


public:

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual char GetBackgroundLayer();
    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);
};

#endif