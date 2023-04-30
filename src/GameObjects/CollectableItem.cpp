#include "CollectableItem.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void CollectableItem::Start() {

    Interactuable::Start();
    InitSprite(SPRITE_SHEET);
}

void CollectableItem::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(13));
}

void CollectableItem::Interact() {
    GameManager::GetInstance()->GetInventory()->AddInventoryItem(ItemIndex::ITEM_BOLT, 1);
    GameManager::GetInstance()->GetCurrentGameScene()->DestroyEnemyCollectable(this);
    Interactuable::Interact();
}
