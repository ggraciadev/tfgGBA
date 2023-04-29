#include "GUI/GUIWorldSpace.h"
#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

bn::fixed_point GUIWorldSpace::GetScreenPosition() const {
    bn::fixed_point pos = GUIWidget::GetScreenPosition();
    if(camera != nullptr) {
        pos -= camera->GetWorldPosition();
    }
    return pos;
}


void GUIWorldSpace::SetGraphic(HUDGraphics graphic) {
    currentGraphic = graphic;
    sprite->set_tiles(spriteItem->tiles_item().create_tiles((int)graphic));
    
}