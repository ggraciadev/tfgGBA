#ifndef BF_MAP_ROOM_H
#define BF_MAP_ROOM_H

#include <bn_point.h>
#include <bn_random.h>

#define GROUND_MIN_HEIGHT 1
#define CEIL_MIN_HEIGHT 1
#define LEFT_WALL_WIDTH 1
#define RIGHT_WALL_WIDTH 1

#define PLATFORM_MIN_WIDTH 4
#define PLATFORM_MAX_WIDTH 6
#define PLATFORM_MIN_HEIGHT 1
#define PLATFORM_MAX_HEIGHT 1
#define PLAYER_JUMP_WIDTH 8
#define PLAYER_JUMP_HEIGHT 4

#define MIN_HORIZONTAL_SUBDIVISION 20
#define MIN_HORIZONTAL_BLOCK_PLATFORM 4
#define MAX_HORIZONTAL_BLOCK_PLATFORM 8
#define HORIZONTAL_SUBDIVISION_WALL_WIDTH 3
#define HORIZONTAL_SUBDIVISION_GROUND_HEIGHT 2
#define HORIZONTAL_SUBDIVISION_OFFSET 6
#define HORZONTAL_SUBDIVISION_DOOR_SIZE 8

#define GROUND_NOISE_TILE_WIDTH 8
#define GROUND_NOISE_TILE_HEIGHT 1
#define MIN_GROUND_NOISE_TILES_HEIGHT 0
#define MAX_GROUND_NOISE_TILES_HEIGHT 2

#define ROOM_MIN_SIZE 24
#define ROOM_MAX_SIZE 30
#define ROOM_DOOR_SIZE 16

class MapLayer;
class MapCollision;

class MapRoom {

    friend class MapGenerator;

public: 
    MapRoom() = default;
    ~MapRoom() = default;

protected:

    MapRoom* leftRoom;
    MapRoom* rightRoom;
    MapRoom* upRoom;
    MapRoom* downRoom;
    
    bn::point pos;
    bn::point size;

    bn::point centralPlatformPos;
    bn::point upRoomPlatformPosCenter;
    bn::point upRoomPlatformPosTop;
    int centralPlatformSize;


public:
    void InitRoom();
    void InitRoom(bn::point _size);
    void InitRoom(bn::point _pos, bn::point _size);

    inline void SetRoomSize(bn::point _size) { size = _size; }
    inline void SetRoomPosition(bn::point _pos) { pos = _pos; }

    inline void SetLeftRoom(MapRoom* room) { leftRoom = room; if(room != nullptr) room->rightRoom = this; }
    inline void SetRightRoom(MapRoom* room) { rightRoom = room; if(room != nullptr) room->leftRoom = this; }
    inline void SetUpRoom(MapRoom* room) { upRoom = room; if(room != nullptr) room->downRoom = this; }
    inline void SetDownRoom(MapRoom* room) { downRoom = room; if(room != nullptr) room->upRoom = this; }

    inline void SetCentralPlatformPos(bn::point p) { centralPlatformPos = p; }
    inline void SetCentralPlatoformSize(int s) { centralPlatformSize = s; }

    //para generar el interior de la sala y los graficos
    void GenerateRoomInterior(MapLayer& map, bn::random& rand);
    

protected:
};

#endif