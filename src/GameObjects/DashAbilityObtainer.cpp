#include "DashAbilityObtainer.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void DashAbilityObtainer::Start() {

    Interactuable::Start();
    InitSprite(SPRITE_SHEET);
}

void DashAbilityObtainer::InitSprite(const bn::sprite_item& item) {
    Interactuable::InitSprite(item);
    sprite->set_tiles(SPRITE_SHEET.tiles_item().create_tiles(14));
}

void DashAbilityObtainer::Interact() {
    player->SetDashAvailable(true);
    GameManager::GetInstance()->GetCurrentGameScene()->DestroyDashAbilityObtainer(this);
    Interactuable::Interact();
}
