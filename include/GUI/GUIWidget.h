#ifndef BF_GUI_WIDGET_H
#define BF_GUI_WIDGET_H

#include <bn_fixed_point.h>
#include <bn_optional.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_sprite_item.h>
#include "GameObjects/Camera.h"

#define GUI_SCREEN_WIDTH 240
#define GUI_SCREEN_HEIGHT 160

enum HUDGraphics { GUI_BUTTON_UNSELECTED, GUI_BUTTON_SELECTED, GUI_A_BUTTON, GUI_B_BUTTON, GUI_R_BUTTON, GUI_L_BUTTON, GUI_FULL_HEART, GUI_HALF_HEART, GUI_EMTPY_HEART, GUI_STR_POWUP, GUI_DEF_POWUP };


class GUIWidget
{
public:
    GUIWidget() = default;
    virtual ~GUIWidget() = default;

protected:
    bn::optional<bn::sprite_ptr> sprite;
    bn::optional<bn::sprite_item> spriteItem;

    GUIWidget* parent;
    bn::fixed_point relativePosition;
    bool enabled;

public:

    virtual void Start();
    void InitGraphic();
    virtual void Render();

    virtual bn::fixed_point GetScreenPosition() const;
    inline void SetRelativePosition(bn::fixed_point pos) { relativePosition = pos; };
    void SetSpriteItem(const bn::sprite_item& item);
    
    inline void SetParent(GUIWidget* p) { parent = p; }
    inline void SetEnabled(bool e) { enabled = e; }
    inline bool IsEnabled() const { return enabled; }

};


#endif