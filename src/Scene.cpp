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
    
    layer.Start();
    layer.SetLayerDepth(0);
    layer.SetCamera(&camera);
    objects.push_back(&layer);

    int n = 1;
    int start = 2;
    int end = n + start;

    for (int i = start; i < end; ++i) {
        objects.push_back(characterFactory.Create());
        objects[i]->Start();
        //characters.push_back(Character());
        //objects.push_back(characterFactory.Get(i));
        objects[i]->AddLocalOffset(i * 10, 0);
        objects[i]->SetLayerDepth(0);
        objects[i]->SetCamera(&camera);
    }
    camera.SetFollowObject(objects[start]);


    gameObjectListSize = objects.size();
}

void Scene::Update() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Update();
    }
}

void Scene::Render() {
    for (int i = 0; i < gameObjectListSize; ++i) {
        objects[i]->Render();
    }
}