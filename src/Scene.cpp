#include "Scene.h"
#include "bn_keypad.h"

#include "bn_sprite_items_character.h"
#include "bn_sprite_items_bolardo.h"
#include "bn_sprite_items_farola.h"
#include "bn_sprite_items_train.h"

#include "bn_regular_bg_items_back.h"
#include "bn_regular_bg_items_b0.h"
#include "bn_regular_bg_items_b1.h"
#include "bn_regular_bg_items_b2.h"

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

    foreGround = new Layer();
    foreGround->SetCamera(mainCamera);
    layer2 = new Layer();
    layer2->SetBackground(bn::regular_bg_items::b2.create_bg(0, 0), 2);
    layer2->SetCamera(mainCamera);
    layer1 = new Layer();
    layer1->SetBackground(bn::regular_bg_items::b1.create_bg(0, 0), 1);
    layer1->SetCamera(mainCamera);
    layer0 = new Layer();
    layer0->SetBackground(bn::regular_bg_items::b0.create_bg(0, 0), 0);
    layer0->SetCamera(mainCamera);


    Player* player = new Player(50,0, layer0);
    player->SetSprite(bn::sprite_items::character.create_sprite(0, 0));
    player->SetCurrentMovementSpeed(1);
    player->SetInputMovement(-0.5f, 0);
    playerController->Possess(player);
    player->SetCamera(mainCamera);

    mainCamera->SetFollowActor(player);
    gameObjectList.push_back(player);
    
    Actor* obj;

    gameObjectList.push_back(new Actor(50,0, layer1));
    obj = (Actor*)gameObjectList[1];
    obj->SetSprite(bn::sprite_items::bolardo.create_sprite(0, 0));
    obj->SetCamera(mainCamera);

    gameObjectList.push_back(new Actor(0,-50, layer2));
    obj = (Actor*)gameObjectList[2];
    obj->SetSprite(bn::sprite_items::train.create_sprite(0,0));
    obj->SetCamera(mainCamera);

    gameObjectList.push_back(new Actor(0,0, foreGround));
    obj = (Actor*)gameObjectList[3];
    obj->SetSprite(bn::sprite_items::farola.create_sprite(0, 0));
    obj->SetCamera(mainCamera);

    gameObjectListSize = gameObjectList.size();

    foreGround->SetLayerDepth(-1);
    layer0->SetLayerDepth(0);
    layer1->SetLayerDepth(1);
    layer2->SetLayerDepth(2);

}

void Scene::Update() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        if(gameObjectList[i] != nullptr) {
            gameObjectList[i]->Update();
        }
    }
    mainCamera->Update();

    foreGround->Update();
    layer0->Update();
    layer1->Update();
    layer2->Update();
}

void Scene::Render() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        if(gameObjectList[i] != nullptr) {
            gameObjectList[i]->Render();
        }
    }
    foreGround->Render();
    layer0->Render();
    layer1->Render();
    layer2->Render();
}