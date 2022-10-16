#include "Scene.h"
#include "bn_keypad.h"

#include "bn_sprite_items_character.h"
#include "bn_sprite_items_bolardo.h"
#include "bn_sprite_items_train.h"

#include "Actor.h"
#include "GameManager.h"

#include "PlayerController.h"
#include "Player.h"

Scene::Scene() {
    gameObjectList.clear();
    gameObjectListSize = 0;
}   

Scene::~Scene() {
    int size = gameObjectList.size();
    for(int i = 0; i < size; ++i) {
        if(gameObjectList[i] != nullptr) {
            delete(gameObjectList[i]);
        }
    }
}


void Scene::Start() {
    PlayerController* playerController = new PlayerController();

    mainCamera = new Camera();
    Player* player = new Player(50,0);
    player->SetSprite(bn::sprite_items::character.create_sprite(0, 0));
    player->SetCurrentMovementSpeed(1);
    player->SetInputMovement(-0.5f, 0);
    playerController->Possess(player);
    player->SetCamera(mainCamera);

    mainCamera->SetFollowActor(player);
    gameObjectList.push_back(player);
    
    Actor* obj;

    gameObjectList.push_back(new Actor(50,0));
    obj = (Actor*)gameObjectList[1];
    obj->SetSprite(bn::sprite_items::bolardo.create_sprite(0, 0));
    //obj->SetCamera(followCamera);

    gameObjectList.push_back(new Actor(0,-50));
    obj = (Actor*)gameObjectList[2];
    obj->SetSprite(bn::sprite_items::train.create_sprite(0, 0));
    obj->SetSprite(bn::sprite_items::bolardo.create_sprite(0, 0));
    obj->SetCurrentMovementSpeed(1);
    obj->SetInputMovement(-0.5f, 0);
    obj->SetGrounded(true);
    obj->SetCamera(mainCamera);

    gameObjectListSize = gameObjectList.size();

}

void Scene::Update() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        if(gameObjectList[i] != nullptr) {
            gameObjectList[i]->Update();
        }
    }
    mainCamera->Update();
}

void Scene::Render() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        if(gameObjectList[i] != nullptr) {
            gameObjectList[i]->Render();
        }
    }
}