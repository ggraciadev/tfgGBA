#ifndef BF_WIDGET_HUD_H
#define BF_WIDGET_HUD_H

#include "WidgetElementHUD.h"
#include "bn_vector.h"

#define MAX_HEARTS 6

class WidgetHUD : public GUIWidget
{
public:
    WidgetHUD() = default;
    virtual ~WidgetHUD() = default;

protected:
    bn::vector<WidgetElementHUD, MAX_HEARTS> hearts;
    WidgetElementHUD strPowerUp;
    WidgetElementHUD defPowerUp;

    int maxHealth;

    void InitHUD();

public:
    virtual void Start();
    virtual void Render();

    void SetMaxHealth(int health);
    void SetCurrentHealth(int health);

    void SetStrPowerUp(bool enabled);
    void SetDefPowerUp(bool enabled);

};


#endif