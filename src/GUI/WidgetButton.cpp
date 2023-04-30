#include "GUI/WidgetButton.h"

#include "bn_sprite_items_miscellaneous.h"
#define SPRITE_SHEET bn::sprite_items::miscellaneous

void WidgetButton::Start() {
    GUIWidget::Start();
    SetSpriteItem(SPRITE_SHEET);
}
void WidgetButton::SetSelected(bool selected) {
    if(selected != buttonSelected) {
        if(selected) {
            currentGraphic = HUDGraphics::GUI_BUTTON_SELECTED;
        }
        else {
            currentGraphic = HUDGraphics::GUI_BUTTON_UNSELECTED;
        }
        buttonSelected = selected;
        sprite->set_tiles(spriteItem->tiles_item().create_tiles((int)currentGraphic));
    }
}