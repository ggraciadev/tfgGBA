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

#include "bn_sprite_items_shop_b0.h"
#define SPRITE_SHEET_SHOP bn::sprite_items::shop_b0

#include "bn_sprite_items_ai_house_b1.h"
#define SPRITE_SHEET_HOUSE_B1 bn::sprite_items::ai_house_b1

#include "bn_sprite_items_ai_house_b2.h"
#define SPRITE_SHEET_HOUSE_B2 bn::sprite_items::ai_house_b2

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
    camera.Start();
    objects.push_back(&camera);
    
    mapLayer.Start(LayerType::CITY_LAYER_0);
    mapLayer.SetLayerDepth(0);
    mapLayer.SetCamera(&camera);
    objects.push_back(&mapLayer);

    layer1.Start(LayerType::CITY_LAYER_1);
    layer1.SetLayerDepth(1);
    layer1.SetCamera(&camera);
    objects.push_back(&layer1);

    layer2.Start(LayerType::CITY_LAYER_2);
    layer2.SetLayerDepth(2);
    layer2.SetCamera(&camera);
    objects.push_back(&layer2);


    objects.push_back(characterFactory.Create());
    objects[4]->SetParent(&mapLayer);
    objects[4]->SetLocalPosition(0, -20);
    objects[4]->Start();
    objects[4]->SetLayerDepth(0);
    objects[4]->SetCamera(&camera);
    objects[4]->SetMapCollision(mapLayer.GetMapCollision());

    int start = 5;
    int end = start + 1;

    // for(int i = start; i < end; ++i) {
    //     objects.push_back(bg0ElementsFactory.Create());
    //     objects[i]->SetSpriteItem(SPRITE_SHEET_SHOP);
    //     objects[i]->SetParent(&mapLayer);
    //     objects[i]->SetLocalPosition(0,0);
    //     objects[i]->Start();
    //     objects[i]->SetLayerDepth(0);
    //     objects[i]->SetCamera(&camera);
    // }

    // start = end;
    end = start + 2;

    for(int i = start; i < end; ++i) {
        objects.push_back(bg1ElementsFactory.Create());
        objects[i]->SetSpriteItem(SPRITE_SHEET_HOUSE_B1);
        objects[i]->SetParent(&layer1);
        objects[i]->SetLocalPosition((i-start-1) * 200,-80);
        objects[i]->Start();
        objects[i]->SetLayerDepth(1);
        objects[i]->SetCamera(&camera);
    }
    start = end;
    end = start + 5;

    for(int i = start; i < end; ++i) {
        objects.push_back(bg2ElementsFactory.Create());
        objects[i]->SetSpriteItem(SPRITE_SHEET_HOUSE_B2);
        objects[i]->SetParent(&layer2);
        objects[i]->SetLocalPosition((i-start-2) * 90,-50);
        objects[i]->Start();
        objects[i]->SetLayerDepth(2);
        objects[i]->SetCamera(&camera);
    }
    
    camera.SetFollowObject(objects[4]);


    gameObjectListSize = objects.size();
}

void Scene::Update() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Update();
    }
}

void Scene::PhysicsUpdate() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->PhysicsUpdate();
    }
}

void Scene::Render() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Render();
    }
}