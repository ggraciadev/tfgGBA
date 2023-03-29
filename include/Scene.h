#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "GameObjects/BackgroundElement.h"
#include "GameObjects/MapLayer.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Layer.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/Attack.h"
#include "Factory.h"

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
    Layer<64,64> layer1;
    Layer<64,64> layer2;
    Factory<Player, 1> player;
    Factory<Character, 10> characterFactory;
    Factory<Enemy, 1> enemy;
    Factory<BackgroundElement<4,4>, 1> bg0ElementsFactory;
    Factory<BackgroundElement<2,2>, 2> bg1ElementsFactory;
    Factory<BackgroundElement<1,1>, 5> bg2ElementsFactory;
    Factory<Attack, 2> attackFactory;
    bn::vector<GameObject*, 20> objects;
    bn::vector<Character*, 50> characters;
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

    bn::vector<Character*, 16> GetAllInstancesCharacters();
    void SpawnAttack(GameObject* parent, Character* creator, bn::fixed_point position, int direction, AttackInfo& attackInfo);
    void DestroyAttack(Attack* atk);
    
};

#endif