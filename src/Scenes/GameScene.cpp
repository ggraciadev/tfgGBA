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
    enemyFactory.Clear();
    enemyBossFactory.Clear();
    attackFactory.Clear();
    collectableItemFactory.Clear();
    atkPowerUpFactory.Clear();
    defPowerUpFactory.Clear();
    doorInteractuableFactory.Clear();
    characters.clear();
    gameObjects.clear();
    currentRoom = -1;
    lastRoom = -1;

    for(int i = 0; i < MAX_MAP_ROOMS; ++i) {
        enemyDefeated[i] = false;
        enemiesInRoom[i] = nullptr;
    }
    enemyDefeated[0] = true;
}

void GameScene::GenerateMap(unsigned seed) {
    //limpieza de memoria
    ClearAllScene();
    mapGenerator.GenerateMap(&map, seed);
    gameObjects.push_back(player);
    characters.push_back(player);
    MapRoom* first = map.GetRoomByIndex(0);
    int offsetX = MAP_WIDTH * TILE_WIDTH / 2;
    int offsetY = MAP_HEIGHT * TILE_HEIGHT / 2;
    bn::fixed_point playerPos = first->GetCentralPlatformPos();
    playerPos.set_x((playerPos.x() + first->GetCentralPlatoformSize() / 2)* TILE_WIDTH - offsetX);
    playerPos.set_y((playerPos.y() -6)* TILE_WIDTH - offsetY);
    
    player->SetLocalPosition(playerPos);
    //player->SetLocalPosition(0,0);

    // EnemyDalek* tmpEnemy = enemy.Create();
    // InitCharacter(tmpEnemy, &map.mapLayer, bn::fixed_point(64, -20), 1);
    currentRoom = 0;
    lastRoom = 0;
    SpawnAdjacentRoomsEnemies();
    //SpawnBoss();
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
    CheckPlayerRoom();
    map.Update();
}

void GameScene::CheckPlayerRoom() {
    int roomIndex = map.GetRoomIndexByPosition(player->GetWorldPosition());
    if(roomIndex != currentRoom) {
        lastRoom = currentRoom;
        currentRoom = roomIndex;
        DespawnPreviousEnemies();
        SpawnAdjacentRoomsEnemies();
    }
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

void GameScene::DespawnPreviousEnemies() {
    bn::vector<int,4> prevAdjacent;
    for(int i = 0; i < 4; ++i) {
        prevAdjacent.push_back(-1);
    }
    bn::vector<int,4> currentAdjacent;
    for(int i = 0; i < 4; ++i) {
        currentAdjacent.push_back(-1);
    }

    map.GetAdjacentRoomIndex(lastRoom, prevAdjacent);
    map.GetAdjacentRoomIndex(currentRoom, currentAdjacent);

    int toDespawnRooms[4] = {-1,-1,-1,-1};
    for(int i = 0; i < 4; ++i) {
        bool found = false;
        for(int j = 0; j < 4 && !found; ++j) {
            if(prevAdjacent[i] == currentAdjacent[j] || prevAdjacent[i] == currentRoom) {
                found = true;
            }
        }
        if(!found) {
            toDespawnRooms[i] = prevAdjacent[i];
        }
    }

    for(int i = 0; i < 4; ++i) {
        if(toDespawnRooms[i] != -1 && enemiesInRoom[toDespawnRooms[i]] != nullptr) {
            DespawnEnemy(enemiesInRoom[toDespawnRooms[i]]);
            enemiesInRoom[toDespawnRooms[i]] = nullptr;
        }
    }
}

void GameScene::SpawnAdjacentRoomsEnemies() {
    bn::vector<int, 4> currentAdjacent;
    for(int i = 0; i < 4; ++i) {
        currentAdjacent.push_back(-1);
    }
    map.GetAdjacentRoomIndex(currentRoom, currentAdjacent);

    for(int i = 0; i < 4; ++i) {
        if(enemiesInRoom[currentAdjacent[i]] == nullptr && !enemyDefeated[currentAdjacent[i]]) {
            SpawnEnemy(currentAdjacent[i]);
        }
    }
}



void GameScene::SpawnEnemy(int roomIndex) {
    MapRoom* mapRoom = map.GetRoomByIndex(roomIndex);
    if(mapRoom->IsBossRoom()) {
        SpawnBoss();
        return;
    }

    bn::fixed_point position(0,0);
    int offsetX = MAP_WIDTH * TILE_WIDTH / 2;
    int offsetY = MAP_HEIGHT * TILE_HEIGHT / 2;

    position.set_x((mapRoom->GetCentralPlatformPos().x() + mapRoom->GetCentralPlatoformSize() / 2) * TILE_WIDTH - offsetX);
    position.set_y((mapRoom->GetCentralPlatformPos().y() - 6) * TILE_HEIGHT - offsetY);

    EnemyDalek* tmpEnemy = enemyFactory.Create();
    InitCharacter(tmpEnemy, &map.mapLayer, position, 1);
    enemiesInRoom[roomIndex] = tmpEnemy;
    
}

void GameScene::DespawnEnemy(Character* enemy) {
    for(int i = gameObjects.size()-1; i >= 0; --i) {
        if(enemy->Equals(gameObjects[i])) {
            enemy->SetLocalPosition(-500, -500);
            enemy->Render();
            gameObjects[i] = nullptr;
            break;
        }
    }
    enemyFactory.Destroy((EnemyDalek*)enemy);
    enemy->SetDestroyed(true);
}

void GameScene::DestroyEnemy(Character* enemy) {
    DespawnEnemy(enemy);
    int roomIndex = map.GetRoomIndexByPosition(enemy->GetWorldPosition());
    if(roomIndex != -1) {
        enemyDefeated[roomIndex] = true;
        enemiesInRoom[roomIndex] = nullptr;
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
            break;
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
    
    enemiesInRoom[map.GetRoomIndex(bossRoom)] = tmpEnemy;
    
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

void GameScene::SpawnHealthRecovery(bn::fixed_point position) {
    HealthInteractuable* tmpInter = healthInteractuableFactory.Create();
    InitGameObject(tmpInter, &map.mapLayer, position, 0);
}

void GameScene::DestroyHealthRecovery(HealthInteractuable* interact) {
    DestroyGameObject(interact);
    healthInteractuableFactory.Destroy(interact);
}