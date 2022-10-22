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

    int n = 1;
    int start = 4;
    int end = n + start;

    for (int i = start; i < end; ++i) {
        objects.push_back(characterFactory.Create());
        //characters.push_back(Character());
        //objects.push_back(characterFactory.Get(i));
        objects[i]->SetParent(&mapLayer);
        objects[i]->SetLocalPosition((i-start) * 10, -20);
        objects[i]->Start();
        objects[i]->SetLayerDepth(0);
        objects[i]->SetCamera(&camera);
        objects[i]->SetMapCollision(mapLayer.GetMapCollision());
    }
    camera.SetFollowObject(objects[start]);


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