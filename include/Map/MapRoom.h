#ifndef BF_MAP_ROOM_H
#define BF_MAP_ROOM_H

#include <bn_point.h>

class MapLayer;
class MapCollision;

class MapRoom {

    friend class MapGenerator;

public: 
    MapRoom() = default;
    ~MapRoom() = default;

protected:

    bn::point pos;
    bn::point size;

    MapRoom* leftRoom;
    MapRoom* rightRoom;
    MapRoom* upRoom;
    MapRoom* downRoom;

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
    void GenerateRoomInterior(MapLayer& map);
    

protected:
    //Para hacer los bordes de la sala
    void GenerateRoomWalls(MapCollision* mapCollisions);
    //Para hacer las connexiones entre salas
    void GenerateRoomDoors(MapCollision* mapCollisions);
    //Para hacer las connexiones entre salas
    void GenerateRoomDoor(bn::point begin,bn::point end, MapCollision* mapCollisions);
    //Para llenar la sala de plataformas
    void GenerateRoomPlatforms(MapCollision* mapCollisions);
    //Para asignar las colisiones de la sala
    void GenerateMapCollisions(MapCollision* mapCollisions);
    //Para asignar Tiles a la sala
    void GenerateRoomTiles(MapLayer& map);
};

#endif