#ifndef BF_GAME_OVER_SCENE_H
#define BF_GAME_OVER_SCENE_H

#include "Scenes/Scene.h"
#include "GameObjects/BasicLayer.h"
#include "GUI/WidgetGameOver.h"

class GameOverScene : public Scene {

public:
    GameOverScene() = default;
    virtual ~GameOverScene() = default;

protected:
    BasicLayer background;
    WidgetGameOver widgetGameOver;

public:
    virtual void Start();
    virtual void Update();
    virtual void Render();

};


#endif