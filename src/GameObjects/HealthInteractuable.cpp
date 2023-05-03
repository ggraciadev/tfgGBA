#include "HealthInteractuable.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void HealthInteractuable::Start() {

    Interactuable::Start();
    InitSprite(SPRITE_SHEET);
}

void HealthInteractuable::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(HUDGraphics::GUI_FULL_HEART));
}

void HealthInteractuable::Interact() {
    player->SetFullHealth();
    GameManager::GetInstance()->GetCurrentGameScene()->DestroyHealthRecovery(this);
    Interactuable::Interact();
}
