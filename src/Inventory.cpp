#include "Inventory.h"

void Inventory::ResetInventory() {
    for(int i = 0; i < (int)ItemIndex::ITEM_END; ++i) {
        inventoryItems[i].quantity = 0;
    }
}