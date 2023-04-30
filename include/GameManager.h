#ifndef BF_GAME_MANAGER_H
#define BF_GAME_MANAGER_H

#include "bn_core.h"
#include "bn_optional.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_text_generator.h"
#include "Scenes/Scene.h"

#include "Scenes/GameScene.h"

#include "Inventory.h"

enum GameScenes { SCENE_SPLASH_SCREEN, SCENE_MAIN_MENU, SCENE_GAME, SCENE_DEATH_MENU };

class GameManager { //Singleton

protected:

    static GameManager* instance;
    Scene* scene;
    Inventory inventory;

    GameScenes currentGameScene;

    bn::string<64> printString;
    bn::sprite_text_generator* textGen;

    unsigned initSeed;

    bool changingScene;

    void InternalChangeScene();

    GameManager();

public:
    ~GameManager();
    static GameManager* GetInstance();

    void Init();

    void Update();
    void PhysicsUpdate();
    void Render(bn::sprite_text_generator& t);
    GameScene* GetCurrentGameScene();

    Inventory* GetInventory() { return &inventory; }

    void PlayGame();
    void ChangeScene(GameScenes sceneToGo);


};

#endif