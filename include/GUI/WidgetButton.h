#ifndef BF_WIDGET_BUTTON_H
#define BF_WIDGET_BUTTON_H

#include "GUIWidget.h"

class WidgetButton : public GUIWidget
{
public:
    WidgetButton() = default;
    virtual ~WidgetButton() = default;

protected:
    HUDGraphics currentGraphic;
    void SetGraphic(HUDGraphics graphic);
    bool buttonSelected;

public:
    virtual void Start();
    void SetSelected(bool selected);
    inline bool GetSelected() const { return buttonSelected; }

};


#endif