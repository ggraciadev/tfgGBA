#ifndef BF_MAIN_MENU_SCENE_H
#define BF_MAIN_MENU_SCENE_H

#include "Scenes/Scene.h"
#include "GameObjects/BasicLayer.h"
#include "GUI/WidgetMainMenu.h"

class MainMenuScene : public Scene {

public:
    MainMenuScene() = default;
    virtual ~MainMenuScene() = default;

protected:
    BasicLayer background;
    WidgetMainMenu widgetMainMenu;

public:
    virtual void Start();
    virtual void Update();
    virtual void Render();

};


#endif