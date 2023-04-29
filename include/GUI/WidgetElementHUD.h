#ifndef BF_WIDGET_ELEMENT_HUD_H
#define BF_WIDGET_ELEMENT_HUD_H

#include "GUIWidget.h"

enum HUDGraphics { GUI_A_BUTTON, GUI_B_BUTTON, GUI_R_BUTTON, GUI_L_BUTTON, GUI_FULL_HEART, GUI_HALF_HEART, GUI_EMTPY_HEART, GUI_STR_POWUP, GUI_DEF_POWUP };


class WidgetElementHUD : public GUIWidget
{
public:
    WidgetElementHUD() = default;
    ~WidgetElementHUD() = default;

protected:
    HUDGraphics currentGraphic;

public:
    virtual void Start();

    void SetGraphic(HUDGraphics graphic);

};


#endif