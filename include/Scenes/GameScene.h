#ifndef BF_GAME_SCENE_H
#define BF_GAME_SCENE_H

#include "Scenes/Scene.h"
#include "Map/Map.h"
#include "Map/MapGenerator.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "GameObjects/EnemyDalek.h"
#include "GameObjects/Attack.h"
#include "GameObjects/CollectableItem.h"
#include "GameObjects/AtkPowerUpInteractuable.h"
#include "GameObjects/DefPowerUpInteractuable.h"
#include "../Factory.h"

#include "bn_vector.h"

class GameScene : public Scene {
public:
    GameScene() = default;
    virtual ~GameScene() = default;

protected:
    Camera camera;
    WidgetHUD widgetHUD;
    Player* player;
    Factory<Player, 1> playerFactory;
    Factory<EnemyDalek, 10> enemy;
    Factory<Attack, 20> attackFactory;
    Factory<CollectableItem, 10> collectableItemFactory;
    Factory<AtkPowerUpInteractuable, 10> atkPowerUpFactory;
    Factory<DefPowerUpInteractuable, 10> defPowerUpFactory;

    bn::vector<Character*, 16> characters;
    Map map;
    MapGenerator mapGenerator;

    void InitGameObject(GameObject* character, GameObject* parent, bn::fixed_point pos, int zOrder);
    void InitCharacter(Character* character, GameObject* parent, bn::fixed_point pos, int zOrder);
    void DestroyGameObject(GameObject* go);

public: 

    virtual void Start() override;
    void GenerateMap(unsigned seed);

    virtual void Update() override;

    virtual void PhysicsUpdate() override;

    virtual void Render() override;

    Player* GetPlayer() { return player; }
    bn::vector<Character*, 16> GetAllInstancesCharacters();
    void SpawnAttack(GameObject* parent, Character* creator, bn::fixed_point position, int direction, AttackInfo& attackInfo);
    void DestroyAttack(Attack* atk);

    void DestroyEnemy(Character* enemy);
    void SpawnEnemyCollectable(bn::fixed_point position);
    void SpawnAtkPowerUp(bn::fixed_point position);
    void SpawnDefPowerUp(bn::fixed_point position);

    void DestroyEnemyCollectable(CollectableItem* interact);
    void DestroyAtkPowerUp(AtkPowerUpInteractuable* interact);
    void DestroyDefPowerUp(DefPowerUpInteractuable* interact);

};

#endif