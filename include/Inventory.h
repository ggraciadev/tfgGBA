#ifndef BF_INVENTORY_H
#define BF_INVENTORY_H

#include "bn_vector.h"
#include "ItemInfo.h"
#include "utils.h"

enum ItemIndex { ITEM_BOLT, ITEM_END };

struct InventoryItem {
    ItemInfo item;
    int quantity;

    InventoryItem() {
        item = ItemInfo();
        quantity = 0;
    }

    InventoryItem(ItemInfo& info) {
        item = info;
        quantity = 0;
    }
    InventoryItem(ItemInfo& info, int quant) {
        item = info;
        quantity = quant;
    }
};

class Inventory {

public: 
    Inventory() = default;
    ~Inventory() = default;

protected:
    bn::vector<InventoryItem, (int)ItemIndex::ITEM_END> inventoryItems;

public:
    InventoryItem* GetInventoryItem(ItemIndex index) { return &inventoryItems[(int)index]; }
    void AddInventoryItem(ItemIndex index, int quant) { inventoryItems[(int)index].quantity = Utils::Max(inventoryItems[(int)index].quantity + quant, 0); }
    void SetInventoryItem(ItemIndex index, int quant) { inventoryItems[(int)index].quantity = Utils::Max(quant, 0);}
    void ResetInventory();
};



#endif