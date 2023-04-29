#ifndef BF_WIDGET_ELEMENT_HUD_H
#define BF_WIDGET_ELEMENT_HUD_H

#include "GUIWidget.h"

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