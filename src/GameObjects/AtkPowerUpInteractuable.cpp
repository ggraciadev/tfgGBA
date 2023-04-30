#include "AtkPowerUpInteractuable.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void AtkPowerUpInteractuable::Start() {

    Interactuable::Start();
    InitSprite(SPRITE_SHEET);
}

void AtkPowerUpInteractuable::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(11));
}

void AtkPowerUpInteractuable::Interact() {
    player->AddAtkPowerUp();
    GameManager::GetInstance()->GetCurrentGameScene()->DestroyAtkPowerUp(this);
    Interactuable::Interact();
}
