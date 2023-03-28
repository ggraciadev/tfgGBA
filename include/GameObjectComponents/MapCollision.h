#ifndef BF_MAP_COLLISION_H
#define BF_MAP_COLLISION_H

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_fixed_point.h>

#define MAX_COMPONENTS_COLLISONS 8
#define MAP_WIDTH 256
#define MAP_HEIGHT 128
#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define OFFSET_X 0 + MAP_WIDTH * TILE_WIDTH / 2

#define OFFSET_Y 0 + MAP_HEIGHT * TILE_HEIGHT / 2

enum MapCollisionType {NONE = 0, PLATFORM = 1, COLLISION = 2};

struct Collisions {
    unsigned collision : 2;
};

class MapCollision : public GameObjectComponent{

public:
    MapCollision();
    ~MapCollision();

protected:
    Collisions collisions[MAP_WIDTH * MAP_HEIGHT];

public:

    void Start();

    MapCollisionType GetCollisionByCell(int cellX, int cellY) const;

    inline MapCollisionType GetCollisionByPosition(int posX, int posY) const { return GetCollisionByCell((OFFSET_X + posX) / TILE_WIDTH, (OFFSET_Y + posY) / TILE_HEIGHT); }

    void SetMapCollisionType(int cellX, int cellY, MapCollisionType collisionType);
};

#endif