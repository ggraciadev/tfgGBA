#include "Scene.h"
#include "bn_keypad.h"

#include "bn_sprite_items_train.h"


//#include "Actor.h"
#include "GameManager.h"
#include "Attack.h"
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
    map.SetCamera(&camera);
    map.Start();


    Player* tmpPlayer = player.Create();
    
    tmpPlayer->SetParent(&map.mapLayer);
    tmpPlayer->SetLocalPosition(0, 0);
    tmpPlayer->Start();
    tmpPlayer->SetLayerDepth(0);
    tmpPlayer->SetZOrder(0);
    tmpPlayer->SetCamera(&camera);
    tmpPlayer->SetMapCollision(map.mapLayer.GetMapCollision());
    camera.SetFollowObject(tmpPlayer);

    objects.push_back(tmpPlayer);
    characters.push_back(tmpPlayer);

    EnemyDalek* tmpEnemy = enemy.Create();
    tmpEnemy->SetParent(&map.mapLayer);
    tmpEnemy->SetLocalPosition(64, -20);
    tmpEnemy->Start();
    tmpEnemy->SetPlayer(tmpPlayer);
    tmpEnemy->SetLayerDepth(0);
    tmpEnemy->SetZOrder(1);
    tmpEnemy->SetCamera(&camera);
    tmpEnemy->SetMapCollision(map.mapLayer.GetMapCollision());
    objects.push_back(tmpEnemy);
    characters.push_back(tmpEnemy);

    int start = 2;
    int end = start + 1;

    gameObjectListSize = objects.size();

    mapGenerator.InitMapGenerator(&map);
    mapGenerator.GenerateMap(5);
}

void Scene::Update() {
    camera.Update();
    map.Update();
    for (int i = 0; i < objects.size(); ++i) {
        if(objects[i] != nullptr) {
            objects[i]->Update();
        }
    }
}

void Scene::PhysicsUpdate() {

    for (int i = 0; i < objects.size(); ++i) {
        if(objects[i] != nullptr) {
            objects[i]->PhysicsUpdate();
        }
    }
}

void Scene::Render() {
    map.Render();
    for (int i = 0; i < objects.size(); ++i) {
        if(objects[i] != nullptr) {
            objects[i]->Render();
        }
    }
}

bn::vector<Character*, 16> Scene::GetAllInstancesCharacters() {
    return characters;
}

void Scene::SpawnAttack(GameObject* parent, Character* creator, bn::fixed_point position, int direction, AttackInfo& attackInfo) {
    Attack* tmpAtk = attackFactory.Create();
    if(parent != nullptr) {
        tmpAtk->SetParent(parent);
        tmpAtk->SetLocalPosition(position);
    }
    else {
        tmpAtk->SetParent(&map.mapLayer);
        tmpAtk->SetLocalPosition(creator->GetWorldPosition() + position);
    }
    tmpAtk->SetAttackInfo(attackInfo);
    tmpAtk->Start();
    tmpAtk->SetCharacterCreator(creator);
    tmpAtk->SetLayerDepth(0);
    tmpAtk->SetZOrder(0);
    tmpAtk->SetCamera(&camera);
    tmpAtk->SetDirection(direction);
    
    auto foundPos = bn::find(objects.begin(), objects.end(), nullptr);
    if(foundPos == objects.end()) {
        objects.push_back(tmpAtk);
    }
    else {
        *foundPos = tmpAtk;
    }
}

void Scene::DestroyAttack(Attack* atk) {
    for(int i = objects.size()-1; i >= 0; --i) {
        if(atk->Equals(objects[i])) {
            atk->SetLocalPosition(-500, -500);
            atk->Render();
            objects[i] = nullptr;
        }
    }
    atk->Destroy();
    attackFactory.Destroy(atk);
}