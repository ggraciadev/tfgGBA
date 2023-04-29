#include "GUI/WidgetElementHUD.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void WidgetElementHUD::Start() {
    GUIWidget::Start();
    SetSpriteItem(SPRITE_SHEET);
}

void WidgetElementHUD::SetGraphic(HUDGraphics graphic) {
    if(graphic != currentGraphic) {
        currentGraphic = graphic;
        sprite->set_tiles(spriteItem->tiles_item().create_tiles((int)graphic));
    }
}