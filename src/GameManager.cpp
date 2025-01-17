
#include "bn_core.h"
#include "GameManager.h"
#include "bn_string.h"

#include "Scenes/GameScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/MainMenuScene.h"


GameManager* GameManager::instance;

GameManager::GameManager() {
    
}

GameManager::~GameManager() {
    // if(scene != nullptr) {
    //     delete(scene);
    // }
}

GameManager* GameManager::GetInstance() {
    if(instance == nullptr) {
        instance = new GameManager();
        instance->Init();
    }
    return instance;
}

void GameManager::Init() {
    //scene = new Scene();
    currentGameScene = GameScenes::SCENE_MAIN_MENU;
    InternalChangeScene();
    initSeed = 0;
    

    // bn::ostringstream string_stream(printString);
    // string_stream << MovementComponent::GetClassName();
    // string_stream << " - ";
    // string_stream << GameObjectComponent::GetClassName();
}

void GameManager::Update() {
    if(currentGameScene == GameScenes::SCENE_MAIN_MENU) {
        initSeed++;
        initSeed = initSeed % 100;
    }
    scene->Update();
}

void GameManager::PhysicsUpdate() {
    scene->PhysicsUpdate();
}

void GameManager::PlayGame() {
    inventory.ResetInventory();
    ChangeScene(GameScenes::SCENE_GAME);
}

void GameManager::Render(bn::sprite_text_generator& t) {
    scene->Render();

    if(changingScene) {
        InternalChangeScene();
    }
    
    // bn::vector<bn::sprite_ptr, 32> text_sprites;
    // printString = "lele";
    // t.generate(0, 0, printString, text_sprites);
    bn::core::update();
}

void GameManager::InternalChangeScene() {
    delete(scene);
    switch (currentGameScene)
    {
        case GameScenes::SCENE_SPLASH_SCREEN:
            break;
        case GameScenes::SCENE_MAIN_MENU:
            scene = new MainMenuScene();
            initSeed = 0;
            break;
        case GameScenes::SCENE_GAME:
            scene = new GameScene();
            break;
        case GameScenes::SCENE_DEATH_MENU:
            scene = new GameOverScene();
            break;
        default:
            break;
    }
    scene->Start();
    if(currentGameScene == GameScenes::SCENE_GAME) {
        GetCurrentGameScene()->GenerateMap(initSeed);
    }
    changingScene = false;
}

GameScene* GameManager::GetCurrentGameScene() { 
    return (GameScene*)scene;
}

void GameManager::ChangeScene(GameScenes sceneToGo) {
    currentGameScene = sceneToGo;
    changingScene = true;
}

