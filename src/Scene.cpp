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

//#include "Actor.h"
#include "GameManager.h"
#include "Character.h"
// #include "PlayerController.h"
// #include "Player.h"

Scene::Scene() {
    gameObjectListSize = 0;
}   

Scene::~Scene() {
    //int size = gameObjectList.size();
    // for(int i = 0; i < size; ++i) {
    //     if(gameObjectList[i] != nullptr) {
    //         delete(gameObjectList[i]);
    //     }
    // }
}

void Scene::Start() {


    int n = 128;
    for (int i = 0; i < n; ++i) {
        Character* temp = characterFactory.Create();
        temp->Start();
        characterFactory.Destroy(temp);
    }

    for (int i = 0; i < n; ++i) {
        objects.push_back(characterFactory.Create());
        objects[i]->Start();
        //characters.push_back(Character());
        //objects.push_back(characterFactory.Get(i));
        objects[i]->AddLocalOffset(i * 10, 0);
    }
    gameObjectListSize = 128;
//     PlayerController* playerController = new PlayerController();

//    mainCamera = Camera();

//     foreGround = Layer();
//     foreGround->SetCamera(&(*mainCamera));
//     layer2 = Layer();
//     layer2->SetBackground(bn::regular_bg_items::b2.create_bg(0, 0), 2);
//     layer2->SetCamera(&(*mainCamera));
//     layer1 = Layer();
//     layer1->SetBackground(bn::regular_bg_items::b1.create_bg(0, 0), 1);
//     layer1->SetCamera(&(*mainCamera));
//     layer0 = Layer();
//     layer0->SetBackground(bn::regular_bg_items::b0.create_bg(0, 0), 0);
//     layer0->SetCamera(&(*mainCamera));


//     Player* player;
//     gameObjectList.push_back(Player(50,0));
//     player = (Player*) &(*gameObjectList[0]);
//     player->SetSprite(bn::sprite_items::character.create_sprite(0, 0));
//     playerController->Possess(player);
//     player->SetCamera(&(*mainCamera));

//     mainCamera->SetFollowActor(player);
    
//     Actor* obj;
//     int n = 1;
//     for (int i = 0; i < n; ++i) {
//         gameObjectList.push_back(Actor(32 * i,0));
//         obj = (Actor*) &(*gameObjectList[i+1]);
//         obj->SetSprite(bn::sprite_items::bolardo.create_sprite(0, 0));
//         obj->SetCamera(&(*mainCamera));
//     }


//     gameObjectList.push_back(new Actor(0,-50, layer2));
//     obj = (Actor*)gameObjectList[n+1];
//     obj->SetSprite(bn::sprite_items::train.create_sprite(0,0));
//     obj->SetCamera(mainCamera);

//     gameObjectList.push_back(new Actor(0,0, foreGround));
//     obj = (Actor*)gameObjectList[n+2];
//     obj->SetSprite(bn::sprite_items::farola.create_sprite(0, 0));
//     obj->SetCamera(mainCamera);

//     gameObjectListSize = gameObjectList.size();

//     foreGround->SetLayerDepth(-1);
//     layer0->SetLayerDepth(0);
//     layer1->SetLayerDepth(1);
//     layer2->SetLayerDepth(2);

}

void Scene::Update() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Update();
    }
    //mainCamera->Update();

    // foreGround->Update();
    // layer0->Update();
    // layer1->Update();
    // layer2->Update();
}

void Scene::Render() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Render();
    }
    // for (int i = 0; i < gameObjectListSize; ++i) {
    //     if(gameObjectList[i].has_value()) {
    //         gameObjectList[i]->Render();
    //     }
    // }
    // foreGround->Render();
    // layer0->Render();
    // layer1->Render();
    // layer2->Render();
}