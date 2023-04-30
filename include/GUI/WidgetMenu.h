#ifndef BF_WIDGET_MENU_H
#define BF_WIDGET_MENU_H

#include "GUI/WidgetButton.h"

class WidgetMenu : public GUIWidget {
public:
    WidgetMenu() = default;
    virtual ~WidgetMenu() = default;

protected:
    int currentSelected;
    int maxItems;

    virtual void InitMenu();
    virtual void SetCurrentButtonSelected(int selected);

public:

    void NextButton();
    void PrevButton();

    virtual void Start();
    virtual void Render() {}
    virtual void OnClick() {}

};
#endif