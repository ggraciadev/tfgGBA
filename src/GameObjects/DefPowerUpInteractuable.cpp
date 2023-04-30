#include "DefPowerUpInteractuable.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void DefPowerUpInteractuable::Start() {

    Interactuable::Start();
    InitSprite(SPRITE_SHEET);
}

void DefPowerUpInteractuable::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(10));
}

void DefPowerUpInteractuable::Interact() {
    player->AddDefPowerUp();
    GameManager::GetInstance()->GetCurrentScene()->DestroyDefPowerUp(this);
    Interactuable::Interact();
}
