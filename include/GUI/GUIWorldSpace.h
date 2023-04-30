#ifndef BF_GUI_WORLD_SPACE_H
#define BF_GUI_WORLD_SPACE_H

#include "GUI/GUIWidget.h"
#include "GameObjects/GameObject.h"

class GUIWorldSpace : public GUIWidget {

public:
    GUIWorldSpace() = default;
    virtual ~GUIWorldSpace() = default;

protected:
    GameObject* camera;
    HUDGraphics currentGraphic;


public:
    virtual bn::fixed_point GetScreenPosition() const override;
    inline void SetCamera(GameObject* cam) { camera = cam; }
    void SetGraphic(HUDGraphics graphic);


};

#endif