#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "GameObjects/BackgroundElement.h"
#include "GameObjects/MapLayer.h"
#include "GameObjects/Camera.h"
#include "GameObjects/TiledLayer.h"
#include "GameObjects/Player.h"
#include "GameObjects/EnemyDalek.h"
#include "GameObjects/Attack.h"
#include "GameObjects/Interactuable.h"
#include "Factory.h"
#include "GUI/WidgetHUD.h"

#include <bn_regular_bg_ptr.h>
#include "bn_vector.h"

#include "MapGenerator.h"
#include "Map.h"

class Scene {

public:
    Scene();
    virtual ~Scene();

protected:
    Camera camera;
    WidgetHUD widgetHUD;
    Player* player;
    Factory<Player, 1> playerFactory;
    Factory<Character, 10> characterFactory;
    Factory<EnemyDalek, 1> enemy;
    Factory<BackgroundElement<4,4>, 1> bg0ElementsFactory;
    Factory<BackgroundElement<2,2>, 2> bg1ElementsFactory;
    Factory<BackgroundElement<1,1>, 5> bg2ElementsFactory;
    Factory<Attack, 10> attackFactory;
    Factory<Interactuable, 10> interactuableFactory;

    bn::vector<GameObject*, 50> objects;
    bn::vector<Character*, 10> characters;
    int gameObjectListSize;
    Map map;
    MapGenerator mapGenerator;
    //bn::optional<bn::regular_bg_ptr> back;
    //bn::optional<Camera> mainCamera;

public:

    virtual void Start();

    virtual void Update();

    virtual void PhysicsUpdate();

    virtual void Render();

    Player* GetPlayer() { return player; }
    bn::vector<Character*, 16> GetAllInstancesCharacters();
    void SpawnAttack(GameObject* parent, Character* creator, bn::fixed_point position, int direction, AttackInfo& attackInfo);
    void DestroyAttack(Attack* atk);

    void DestroyEnemy(Character* enemy);
    void SpawnEnemyCollectable(bn::fixed_point position);
    void DestroyEnemyCollectable(Interactuable* interact);
    
};

#endif