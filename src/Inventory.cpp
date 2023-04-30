#include "Inventory.h"

void Inventory::ResetInventory() {
    if(inventoryItems.size() == 0) {
        InitInventory();
    }
    for(int i = 0; i < (int)ItemIndex::ITEM_END; ++i) {
        inventoryItems[i].quantity = 0;
    }
}

void Inventory::InitInventory() {
    ItemInfo temp;
    temp.SetName("Bolt");
    inventoryItems.push_back(InventoryItem(temp, 0));
}