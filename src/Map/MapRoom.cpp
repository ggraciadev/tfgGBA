#include "MapRoom.h"
#include "GameObjects/MapLayer.h"
#include "utils.h"

void MapRoom::InitRoom() {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = bn::point(-1,-1);
    size = bn::point(-1,-1);
    bossRoom = false;
}

void MapRoom::InitRoom(bn::point _size) {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = bn::point(-1,-1);
    size = _size;
    bossRoom = false;
}

void MapRoom::InitRoom(bn::point _pos, bn::point _size) {
    leftRoom = nullptr;
    rightRoom = nullptr;
    upRoom = nullptr;
    downRoom = nullptr;
    pos = _pos;
    size = _size;
    bossRoom = false;
}
