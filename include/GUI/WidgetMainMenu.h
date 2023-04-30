#ifndef BF_WIDGET_MAIN_MUNE_H
#define BF_WIDGET_MAIN_MENU_H

#include "GUI/WidgetMenu.h"

class WidgetMainMenu : public WidgetMenu {
public:
    WidgetMainMenu() = default;
    virtual ~WidgetMainMenu() = default;
protected:
    WidgetButton playButton;

    void OnClickPlay();
    virtual void InitMenu();
    virtual void SetCurrentButtonSelected(int selected);

public:
    virtual void Start();
    virtual void Render();
    virtual void OnClick();
};

#endif