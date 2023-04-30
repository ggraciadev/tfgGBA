#include "Scenes/GameScene.h"
#include "../GameManager.h"

void GameScene::Start() {
    camera.Start();
    map.SetCamera(&camera);
    map.Start();

    widgetHUD.Start();

    player = playerFactory.Create();
    player->SetHUD(&widgetHUD);
    bn::fixed_point pos(0,0);
    InitCharacter(player, &map.mapLayer, pos, 0);
    camera.SetFollowObject(player);

    EnemyDalek* tmpEnemy = enemy.Create();
    pos = bn::fixed_point(64, -20);
    InitCharacter(tmpEnemy, &map.mapLayer, pos, 1);

    mapGenerator.InitMapGenerator(&map);
}

void GameScene::GenerateMap(unsigned seed) {
    mapGenerator.GenerateMap(seed);
}

void GameScene::InitGameObject(GameObject* gameObject, GameObject* parent, bn::fixed_point pos, int zOrder) {
    gameObject->SetParent(parent);
    gameObject->SetLocalPosition(pos);
    gameObject->Start();
    gameObject->SetLayerDepth(0);
    gameObject->SetZOrder(zOrder);
    gameObject->SetCamera(&camera);

    auto foundPos = bn::find(gameObjects.begin(), gameObjects.end(), nullptr);
    if(foundPos == gameObjects.end()) {
        gameObjects.push_back(gameObject);
    }
    else {
        *foundPos = gameObject;
    }
}

void GameScene::InitCharacter(Character* character, GameObject* parent, bn::fixed_point pos, int zOrder) {
    InitGameObject(character, parent, pos, zOrder);
    character->SetMapCollision(map.mapLayer.GetMapCollision());
    characters.push_back(character);
}

void GameScene::Update() {
    camera.Update();
    Scene::Update();
    map.Update();
}

void GameScene::PhysicsUpdate() {
    Scene::PhysicsUpdate();
}

void GameScene::Render() {
    Scene::Render();
    map.Render();
}

bn::vector<Character*, 16> GameScene::GetAllInstancesCharacters() {
    return characters;
}

void GameScene::SpawnAttack(GameObject* parent, Character* creator, bn::fixed_point position, int direction, AttackInfo& attackInfo) {
    Attack* tmpAtk = attackFactory.Create();
    if(parent == nullptr) {
        parent = &map.mapLayer;
        position = creator->GetWorldPosition() + position;
    }
    tmpAtk->SetAttackInfo(attackInfo);
    InitGameObject(tmpAtk, parent, position, 0);
    tmpAtk->SetCharacterCreator(creator);
    tmpAtk->SetDirection(direction);
}

void GameScene::DestroyAttack(Attack* atk) {
    for(int i = gameObjects.size()-1; i >= 0; --i) {
        if(atk->Equals(gameObjects[i])) {
            atk->SetLocalPosition(-500, -500);
            atk->Render();
            gameObjects[i] = nullptr;
        }
    }
    atk->Destroy();
    attackFactory.Destroy(atk);
}

void GameScene::DestroyEnemy(Character* enemy) {
    for(int i = gameObjects.size()-1; i >= 0; --i) {
        if(enemy->Equals(gameObjects[i])) {
            enemy->SetLocalPosition(-500, -500);
            enemy->Render();
            gameObjects[i] = nullptr;
        }
    }
    enemy->Destroy();
}

void GameScene::SpawnEnemyCollectable(bn::fixed_point position) {
    CollectableItem* tmpInter = collectableItemFactory.Create();
    InitGameObject(tmpInter, &map.mapLayer, position, 0);
}

void GameScene::SpawnAtkPowerUp(bn::fixed_point position) {
    AtkPowerUpInteractuable* tmpInter = atkPowerUpFactory.Create();
    InitGameObject(tmpInter, &map.mapLayer, position, 0);
}

void GameScene::SpawnDefPowerUp(bn::fixed_point position) {
    DefPowerUpInteractuable* tmpInter = defPowerUpFactory.Create();
    InitGameObject(tmpInter, &map.mapLayer, position, 0);
}

void GameScene::DestroyGameObject(GameObject* go) {
    for(int i = gameObjects.size()-1; i >= 0; --i) {
        if(go->Equals(gameObjects[i])) {
            go->SetLocalPosition(-500, -500);
            go->Render();
            gameObjects[i] = nullptr;
        }
    }
    go->Destroy();
}

void GameScene::DestroyEnemyCollectable(CollectableItem* interact) {
    DestroyGameObject(interact);
    collectableItemFactory.Destroy(interact);
}

void GameScene::DestroyAtkPowerUp(AtkPowerUpInteractuable* interact) {
    DestroyGameObject(interact);
    atkPowerUpFactory.Destroy(interact);
}

void GameScene::DestroyDefPowerUp(DefPowerUpInteractuable* interact) {
    DestroyGameObject(interact);
    defPowerUpFactory.Destroy(interact);
}