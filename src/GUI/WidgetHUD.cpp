#include "GUI/WidgetHUD.h"

void WidgetHUD::Start() {
    GUIWidget::Start();
    InitHUD();
}

void WidgetHUD::InitHUD() {
    SetEnabled(true);
    for(int i = 0; i < MAX_HEARTS; ++i) {
        hearts.emplace_back(WidgetElementHUD());
        hearts[i].Start();
        hearts[i].SetParent(this);
        hearts[i].SetRelativePosition(bn::fixed_point(-GUI_SCREEN_WIDTH/2 + 10 + 18*i, -GUI_SCREEN_HEIGHT/2 + 8));
    }
    strPowerUp.Start();
    strPowerUp.SetParent(this);
    strPowerUp.SetRelativePosition(bn::fixed_point(-GUI_SCREEN_WIDTH/2 + 10, -GUI_SCREEN_HEIGHT/2 + 26));
    strPowerUp.SetGraphic(HUDGraphics::GUI_STR_POWUP);

    defPowerUp.Start();
    defPowerUp.SetParent(this);
    defPowerUp.SetRelativePosition(bn::fixed_point(-GUI_SCREEN_WIDTH/2 + 28, -GUI_SCREEN_HEIGHT/2 + 26));
    defPowerUp.SetGraphic(HUDGraphics::GUI_DEF_POWUP);

    SetMaxHealth(6);
    SetCurrentHealth(6);
    SetStrPowerUp(false);
    SetDefPowerUp(false);
}

void WidgetHUD::Render() {
    for(int i = 0; i < MAX_HEARTS; ++i) {
        hearts[i].Render();
    }
    strPowerUp.Render();
    defPowerUp.Render();
}

void WidgetHUD::SetMaxHealth(int health) {
    for(int i = 0; i < MAX_HEARTS; ++i) {
        hearts[i].SetEnabled(i < health/2);
    }
    maxHealth = health;
    Render();
}
void WidgetHUD::SetCurrentHealth(int health) {
    for(int i = 0; i < maxHealth / 2; ++i) {
        if(i < health / 2) {
            hearts[i].SetGraphic(HUDGraphics::GUI_FULL_HEART);
        }
        else if(health % 2 == 1 && i == health/2) {
            hearts[i].SetGraphic(HUDGraphics::GUI_HALF_HEART);
        }
        else {
            hearts[i].SetGraphic(HUDGraphics::GUI_EMTPY_HEART);
        }
    }
    Render();
}

void WidgetHUD::SetStrPowerUp(bool enabled) {
    strPowerUp.SetEnabled(enabled);
    Render();
}

void WidgetHUD::SetDefPowerUp(bool enabled) {
    defPowerUp.SetEnabled(enabled);
    Render();
}