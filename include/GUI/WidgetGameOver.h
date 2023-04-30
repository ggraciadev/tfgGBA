#ifndef BF_WIDGET_GAME_OVER_H
#define BF_WIDGET_GAME_OVER_H

#include "GUI/WidgetMenu.h"

class WidgetGameOver : public WidgetMenu {
public:
    WidgetGameOver() = default;
    virtual ~WidgetGameOver() = default;
protected:
    WidgetButton playAgainButton;
    WidgetButton goToMainMenuButton;

    void OnClickPlayAgain();
    void OnClickGoToMainMenu();
    virtual void InitMenu();
    virtual void SetCurrentButtonSelected(int selected);

public:
    virtual void Start();
    virtual void Render();
    virtual void OnClick();
};

#endif