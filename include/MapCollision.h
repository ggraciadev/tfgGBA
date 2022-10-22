#ifndef BF_MAP_COLLISION_H
#define BF_MAP_COLLISION_H

#include "GameObjectComponent.h"
#include <bn_fixed_point.h>

#define MAX_COMPONENTS_COLLISONS 8
#define MAP_WIDTH 64
#define MAP_HEIGHT 32
#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define OFFSET_X 0 + MAP_WIDTH * TILE_WIDTH / 2

#define OFFSET_Y 0 + MAP_HEIGHT * TILE_HEIGHT / 2

enum MapCollisionType {NONE, RAMP_UP, RAMP_DOWN, COLLISION};

class MapCollision : public GameObjectComponent{

public:
    MapCollision();
    ~MapCollision();

protected:
    MapCollisionType collisions[MAP_WIDTH * MAP_HEIGHT];

public:

    virtual void Start() override;
    virtual void Update() override;

    MapCollisionType GetCollisionByCell(int cellX, int cellY);

    MapCollisionType GetCollisionByPosition(int posX, int posY) { return GetCollisionByCell((OFFSET_X + posX) / TILE_WIDTH, (OFFSET_Y + posY) / TILE_HEIGHT); }

};

#endif