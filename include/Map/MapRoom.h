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
#define PLAYER_JUMP_WIDTH 5
#define PLAYER_JUMP_HEIGHT 4

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

    //para generar el interior de la sala y los graficos
    void GenerateRoomInterior(MapLayer& map, bn::random& rand);
    

protected:
    //Para hacer los bordes de la sala
    void GenerateRoomInteriorTiles(MapCollision* mapCollisions);
    //Para hacer los bordes de la sala
    void GenerateRoomWalls(MapCollision* mapCollisions);
    //Para hacer las connexiones entre salas
    void GenerateRoomDoorsAndPlatforms(MapCollision* mapCollisions, bn::random& rand);
    //Para hacer las connexiones entre salas
    void GenerateRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions);
    void GenerateRoomPlatforms(MapCollision* mapCollisions, bn::point otherRoomGroundBegin, bn::point otherRoomGroundEnd, bn::random& rand);
    //Para asignar las colisiones de la sala
    void GenerateMapCollisions(MapCollision* mapCollisions, bn::random& rand);
};

#endif