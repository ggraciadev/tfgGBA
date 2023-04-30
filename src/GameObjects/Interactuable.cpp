#include "GameObjects/Interactuable.h"
#include "GameObjects/Player.h"
#include "GameManager.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous


void Interactuable::Start() {
    player = GameManager::GetInstance()->GetCurrentGameScene()->GetPlayer();
    InitPrompt();

    boxCollision.SetIsTrigger(true);
    boxCollision.Setup(-16,-16,32,32);

    playerTriggered = false;

    AddComponent(&boxCollision);
    GameObject::Start();
}

void Interactuable::InitPrompt() {
    interactivePrompt.SetSpriteItem(SPRITE_SHEET);
    interactivePrompt.Start();
    interactivePrompt.SetRelativePosition(GetWorldPosition() + bn::fixed_point(10,-10));
    interactivePrompt.SetGraphic(HUDGraphics::GUI_A_BUTTON);
}

void Interactuable::InitSprite(const bn::sprite_item& item) {
    sprite = item.create_sprite(GetScreenPosition());
    sprite->set_bg_priority(0);
    sprite->set_z_order(1);
}

void Interactuable::SetCamera(GameObject* cam) {
    camera = cam;
    interactivePrompt.SetCamera(cam);
}

void Interactuable::Update() {
    if(boxCollision.IsColliding(player->GetBoxCollision())) {
        if(!playerTriggered) {
            interactivePrompt.SetCamera(camera);
            OnPlayerTriggerEnter();
        }
    }
    else if(playerTriggered) {
        OnPlayerTriggerExit();
    }
    GameObject::Update();
}
void Interactuable::Render() {
    interactivePrompt.SetRelativePosition(GetWorldPosition());
    interactivePrompt.Render();
    if(sprite.has_value()) {
        sprite->set_position(GetScreenPosition());
    }
    GameObject::Render();
}

void Interactuable::OnPlayerTriggerEnter() {
    SetGraphicEnabled(true);
    player->SetCurrentInteractuable(this, this);
    playerTriggered = true;
}

void Interactuable::OnPlayerTriggerExit() {
    SetGraphicEnabled(false);
    player->SetCurrentInteractuable(nullptr, this);
    playerTriggered = false;
}

void Interactuable::SetGraphicEnabled(bool enabled) {
    interactivePrompt.SetEnabled(enabled);
}

void Interactuable::Interact() {
    player->SetCurrentInteractuable(nullptr, this);
}