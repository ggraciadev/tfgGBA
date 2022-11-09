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
    
    mapLayer.SetCamera(&camera);
    mapLayer.SetLayerDepth(0);
    mapLayer.Start(LayerType::CITY_LAYER_0);

    layer1.SetLayerDepth(1);
    layer1.SetCamera(&camera);
    layer1.Start(LayerType::CITY_LAYER_1);

    layer2.SetLayerDepth(2);
    layer2.SetCamera(&camera);
    layer2.Start(LayerType::CITY_LAYER_2);


    Character* tmpCharacter = characterFactory.Create();
    
    tmpCharacter->SetParent(&mapLayer);
    tmpCharacter->SetLocalPosition(0, -20);
    tmpCharacter->Start();
    tmpCharacter->SetLayerDepth(0);
    tmpCharacter->SetCamera(&camera);
    tmpCharacter->SetMapCollision(mapLayer.GetMapCollision());
    camera.SetFollowObject(tmpCharacter);

    objects.push_back(tmpCharacter);

    int start = 1;
    int end = start + 1;

    // for(int i = start; i < end; ++i) {
    //     objects.push_back(bg0ElementsFactory.Create());
    //     bgEl->SetSpriteItem(SPRITE_SHEET_SHOP);
    //     bgEl->SetParent(&mapLayer);
    //     bgEl->SetLocalPosition(0,0);
    //     bgEl->Start();
    //     bgEl->SetLayerDepth(0);
    //     bgEl->SetCamera(&camera);
    // }

    // start = end;
    end = start + 2;

    for(int i = start; i < end; ++i) {
        BackgroundElement<2,2>* bgEl = bg1ElementsFactory.Create();
        bgEl->SetSpriteItem(SPRITE_SHEET_HOUSE_B1);
        bgEl->SetParent(&layer1);
        bgEl->SetLocalPosition((i-start-1) * 200,-80);
        bgEl->Start();
        bgEl->SetLayerDepth(1);
        bgEl->SetCamera(&camera);
        objects.push_back(bgEl);
    }
    start = end;
    end = start + 5;

    for(int i = start; i < end; ++i) {
        BackgroundElement<1,1>* bgEl = bg2ElementsFactory.Create();
        bgEl->SetSpriteItem(SPRITE_SHEET_HOUSE_B2);
        bgEl->SetParent(&layer2);
        bgEl->SetLocalPosition((i-start-2) * 90,-50);
        bgEl->Start();
        bgEl->SetLayerDepth(2);
        bgEl->SetCamera(&camera);
        objects.push_back(bgEl);
    }
    


    gameObjectListSize = objects.size();
}

void Scene::Update() {
    camera.Update();
    mapLayer.Update();
    layer1.Update();
    layer2.Update();
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
    mapLayer.Render();
    layer1.Render();
    layer2.Render();
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Render();
    }
}