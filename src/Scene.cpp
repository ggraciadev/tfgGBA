#include "Scene.h"
#include "bn_keypad.h"

#include "bn_sprite_items_train.h"


//#include "Actor.h"
#include "GameManager.h"
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

    widgetHUD.Start();

    player = playerFactory.Create();
    
    player->SetParent(&map.mapLayer);
    player->SetLocalPosition(0, 0);
    player->SetHUD(&widgetHUD);
    player->Start();
    player->SetLayerDepth(0);
    player->SetZOrder(0);
    player->SetCamera(&camera);
    player->SetMapCollision(map.mapLayer.GetMapCollision());
    camera.SetFollowObject(player);

    objects.push_back(player);
    characters.push_back(player);

    EnemyDalek* tmpEnemy = enemy.Create();
    tmpEnemy->SetParent(&map.mapLayer);
    tmpEnemy->SetLocalPosition(64, -20);
    tmpEnemy->Start();
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

void Scene::DestroyEnemy(Character* enemy) {
    for(int i = objects.size()-1; i >= 0; --i) {
        if(enemy->Equals(objects[i])) {
            enemy->SetLocalPosition(-500, -500);
            enemy->Render();
            objects[i] = nullptr;
        }
    }
    enemy->Destroy();
}
void Scene::SpawnEnemyCollectable(bn::fixed_point position) {
    Interactuable* tmpInter = interactuableFactory.Create();
    
    tmpInter->SetParent(&map.mapLayer);
    tmpInter->SetLocalPosition(position);
    tmpInter->Start();
    tmpInter->SetLayerDepth(0);
    tmpInter->SetZOrder(0);
    tmpInter->SetCamera(&camera);

    auto foundPos = bn::find(objects.begin(), objects.end(), nullptr);
    if(foundPos == objects.end()) {
        objects.push_back(tmpInter);
    }
    else {
        *foundPos = tmpInter;
    }
}

void Scene::DestroyEnemyCollectable(Interactuable* interact) {
    for(int i = objects.size()-1; i >= 0; --i) {
        if(interact->Equals(objects[i])) {
            interact->SetLocalPosition(-500, -500);
            interact->Render();
            objects[i] = nullptr;
        }
    }
    interact->Destroy();
    interactuableFactory.Destroy(interact);
}