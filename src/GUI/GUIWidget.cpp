#include "GUI/GUIWidget.h"

void GUIWidget::Start(){
    parent = nullptr;
    relativePosition = bn::fixed_point(0,0);
}

void GUIWidget::InitGraphic() {
    sprite = spriteItem->create_sprite(GetScreenPosition());
    sprite->set_bg_priority(0);
    sprite->set_z_order(0);
}

void GUIWidget::Render(){
    sprite->set_position(GetScreenPosition());
}

void GUIWidget::SetSpriteItem(const bn::sprite_item& item) { 
    spriteItem = bn::move(item); 
    InitGraphic();
}

bn::fixed_point GUIWidget::GetScreenPosition() const {
    bn::fixed_point screenPos;
    if(enabled) {
        screenPos = relativePosition;
        if(parent != nullptr) {
            screenPos += parent->GetScreenPosition();
        }
    }
    else {
        screenPos = bn::fixed_point(-1000,-1000);
    }
    return screenPos;
}