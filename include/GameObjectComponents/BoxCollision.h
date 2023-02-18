#ifndef BF_BOX_COLLISION_H
#define BF_BOX_COLLISION_H

#include "GameObjectComponents/GameObjectComponent.h"
#include "MapCollision.h"
#include "bn_vector.h"
#include <bn_fixed_point.h>

#define MAX_COMPONENTS_COLLISONS 8

enum CollisionPositions {TOP_COLLISION, BOT_COLLISION, LEFT_COLLISION, RIGHT_COLLISION};

class GameObject;

struct BoxExtension {
    bn::fixed_point boxOffset;
    bn::fixed_point boxSize;

    BoxExtension() {
        boxOffset = bn::fixed_point(0,0);
        boxSize = bn::fixed_point(1,1);
    };

    BoxExtension(const bn::fixed_point & offset, const bn::fixed_point & size) {
        boxOffset = offset;
        boxSize = size;
    }
};

class BoxCollision : public GameObjectComponent{
public:
    
    BoxCollision();
    virtual ~BoxCollision();

    bn::vector<GameObjectComponent*, MAX_COMPONENTS_COLLISONS> collidingComponents;

    char collisionContacts[4] = {false, false, false, false};

protected:

    MapCollision* mapCollision;  

    bn::fixed_point lastPosition;
    bn::fixed_point movementDirection;
    bn::fixed_point currentPosition;

    BoxExtension extension;

    bool updatedPosition;
    bool isTrigger = false;

public:

    virtual void Start() override;
    virtual void Update() override;

    void Setup(bn::fixed_point offset, bn::fixed_point size);
    inline void Setup(const BoxExtension& boxExt) { extension = boxExt; }
    inline void SetMapCollision(MapCollision* mc) {mapCollision = mc;}
    void Setup(int offX, int offY, int width, int height);


    void UpdateCurrentPosition();
    inline void SetIsTrigger(bool trigger) { isTrigger = trigger; }

    void UpdateContacts();
    MapCollisionType CheckHorizontalCollisions();
    MapCollisionType CheckVerticalCollisions();
    void CheckCollisionWithMap();
    MapCollisionType CheckCollisionWithMapEdge(int startX, int startY, int endX, int endY);

    bool IsColliding(BoxCollision* other);

    bn::fixed_point GetCurrentPosition();

    inline bn::fixed_point GetSize() const {return extension.boxSize;}

    inline bool GetContact(CollisionPositions pos) const { 
        return collisionContacts[pos];
    }

};

#endif