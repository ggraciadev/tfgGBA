#include "Scenes/GameScene.h"
#include "../GameManager.h"

void GameScene::Start() {
    camera.Start();
    map.SetCamera(&camera);
    map.Start();

    widgetHUD.Start();

    player = playerFactory.Create();
    InitCharacter(player, &map.mapLayer, bn::fixed_point(0,0), 0);
    
    player->SetHUD(&widgetHUD);
    camera.SetFollowObject(player);
}

void GameScene::ClearAllScene() {
    enemy.Clear();
    enemyBossFactory.Clear();
    attackFactory.Clear();
    collectableItemFactory.Clear();
    atkPowerUpFactory.Clear();
    defPowerUpFactory.Clear();
    doorInteractuableFactory.Clear();
    characters.clear();
    gameObjects.clear();
}

void GameScene::GenerateMap(unsigned seed) {
    //limpieza de memoria
    ClearAllScene();
    mapGenerator.GenerateMap(&map, seed);
    gameObjects.push_back(player);
    characters.push_back(player);
    player->SetLocalPosition(bn::fixed_point(0,0));
    //player->SetLocalPosition(0,0);

    // EnemyDalek* tmpEnemy = enemy.Create();
    // InitCharacter(tmpEnemy, &map.mapLayer, bn::fixed_point(64, -20), 1);

    SpawnBoss();
    //place player
    //place enemies
    //place doors
}

void GameScene::InitGameObject(GameObject* gameObject, GameObject* parent, bn::fixed_point pos, int zOrder) {
    gameObject->SetParent(parent);
    gameObject->SetLocalPosition(pos);
    gameObject->Init();
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

void GameScene::SpawnBoss() {

    EnemyBoss* tmpEnemy = enemyBossFactory.Create();
    bn::fixed_point position(0,0);
    MapRoom* bossRoom = map.GetBossRoom();
    int offsetX = MAP_WIDTH * TILE_WIDTH / 2;
    int offsetY = MAP_HEIGHT * TILE_HEIGHT / 2;
    position.set_x((bossRoom->GetPosition().x() + bossRoom->GetSize().x() / 2) * TILE_WIDTH - offsetX);
    position.set_y((bossRoom->GetPosition().y() + bossRoom->GetSize().y() - 10) * TILE_HEIGHT - offsetY);

    InitCharacter(tmpEnemy, &map.mapLayer, position, 1);
    
}

void GameScene::SpawnDoorInteractuable() {
    DoorInteractuable* tmpInter = doorInteractuableFactory.Create();
    tmpInter->NextGameSceneSeed(map.GetNextSceneSeed());
    bn::fixed_point position(0,0);
    MapRoom* bossRoom = map.GetBossRoom();
    int offsetX = MAP_WIDTH * TILE_WIDTH / 2;
    int offsetY = MAP_HEIGHT * TILE_HEIGHT / 2;
    position.set_x((bossRoom->GetPosition().x() + bossRoom->GetSize().x() / 2) * TILE_WIDTH - offsetX);
    position.set_y((bossRoom->GetPosition().y() + bossRoom->GetSize().y() - 2) * TILE_HEIGHT - offsetY);
    InitGameObject(tmpInter, &map.mapLayer, position, 0);
}
