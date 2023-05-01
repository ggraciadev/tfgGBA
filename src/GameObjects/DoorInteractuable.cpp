#include "DoorInteractuable.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void DoorInteractuable::Start() {

    Interactuable::Start();
    //InitSprite(SPRITE_SHEET);
}

void DoorInteractuable::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    //sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(12));
}

void DoorInteractuable::Interact() {
    SetGraphicEnabled(false);
    interactivePrompt.Render();
    GameManager::GetInstance()->GetCurrentGameScene()->GenerateMap(nextGameSceneSeed);
    Interactuable::Interact();
}
