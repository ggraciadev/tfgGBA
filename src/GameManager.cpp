
#include "bn_core.h"
#include "GameManager.h"
#include "bn_string.h"

#include "Scenes/GameScene.h"


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
    ChangeScene(GameScenes::SCENE_GAME);
    

    // bn::ostringstream string_stream(printString);
    // string_stream << MovementComponent::GetClassName();
    // string_stream << " - ";
    // string_stream << GameObjectComponent::GetClassName();
}

void GameManager::Update() {
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
    
    // bn::vector<bn::sprite_ptr, 32> text_sprites;
    // printString = "lele";
    // t.generate(0, 0, printString, text_sprites);
    bn::core::update();
}

GameScene* GameManager::GetCurrentGameScene() { 
    if(currentGameScene == GameScenes::SCENE_GAME) {
        return &(gameScene);
    }
    else {
        return nullptr;
    }
}

void GameManager::ChangeScene(GameScenes sceneToGo) {
    currentGameScene = sceneToGo;
    switch (sceneToGo)
    {
        case GameScenes::SCENE_SPLASH_SCREEN:
            break;
        case GameScenes::SCENE_MAIN_MENU:
            break;
        case GameScenes::SCENE_GAME:
            //gameScene = GameScene();
            scene = &(gameScene);
            break;
        case GameScenes::SCENE_DEATH_MENU:
            break;
        default:
            break;
    }
    scene->Start();
}

