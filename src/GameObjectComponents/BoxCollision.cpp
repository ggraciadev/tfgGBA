#include "GameObjectComponents/BoxCollision.h"
#include "GameObjectComponents/MapCollision.h"
#include "GameObjects/GameObject.h"

BoxCollision::BoxCollision() : GameObjectComponent::GameObjectComponent(){
    
}

BoxCollision::~BoxCollision() {

}

void BoxCollision::Setup(bn::fixed_point offset, bn::fixed_point size) {
    extension.boxOffset = offset;
    extension.boxSize = size;
}

void BoxCollision::Setup(int offX, int offY, int width, int height) {
    Setup(bn::fixed_point(offX, offY), bn::fixed_point(width, height));
}

void BoxCollision::Start() {
    updateType = UpdateType::PHYSICS_UPDATE;
    GameObjectComponent::Start();
    currentPosition = gameObject->GetWorldPosition();
}

void BoxCollision::Update() {
    UpdateCurrentPosition();
    if(mapCollision != nullptr && !isTrigger) {
        CheckCollisionWithMap();
        UpdateContacts();
        gameObject->SetLocalPosition(currentPosition - extension.boxOffset);
    }
}

void BoxCollision::UpdateCurrentPosition() {
    lastPosition = currentPosition;
    currentPosition = gameObject->GetWorldPosition() + extension.boxOffset;
    movementDirection = currentPosition - lastPosition;
    updatedPosition = true;
}

bn::fixed_point BoxCollision::GetCurrentPosition() {
    if(!updatedPosition) {
        UpdateCurrentPosition();
    }
    return currentPosition;
}

bool BoxCollision::IsColliding(BoxCollision* other) {
    bn::fixed_point otherPosition = other->GetCurrentPosition();
    bn::fixed_point otherSize = other->GetSize();

    return  currentPosition.x() < otherPosition.x() + otherSize.x() &&
            currentPosition.x() + extension.boxSize.x() > otherPosition.x() &&
            currentPosition.y() < otherPosition.y() + otherSize.y() &&
            currentPosition.y() + extension.boxSize.y() > otherPosition.y();
}

MapCollisionType BoxCollision::CheckCollisionWithMapEdge(int startX, int startY, int endX, int endY) {
    MapCollisionType result = MapCollisionType::ROOM_INTERIOR;
    for(int i = startY; i < endY+1 && result == MapCollisionType::ROOM_INTERIOR; i += TILE_HEIGHT) {
        for(int j = startX; j < endX+1 && result == MapCollisionType::ROOM_INTERIOR; j += TILE_WIDTH) {
            result = mapCollision->GetCollisionByPosition(j, i);
        }
    }

    return result;
}

void BoxCollision::UpdateContacts() {

    if(movementDirection.x() > 0) {
        collisionContacts[LEFT_COLLISION] = false;
    }
    else if(movementDirection.x() < 0) {
        collisionContacts[RIGHT_COLLISION] = false;
    }

    if(movementDirection.y() > 0) {
        collisionContacts[TOP_COLLISION] = false;
    }
    else if(movementDirection.y() < 0) {
        collisionContacts[BOT_COLLISION] = false;
    }
}

MapCollisionType BoxCollision::CheckHorizontalCollisions() {
    MapCollisionType col = MapCollisionType::ROOM_INTERIOR;
    if(movementDirection.x() > 0) {
        int tempStartX = currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer();
        int tempStartY = currentPosition.y().floor_integer();
        int tempEndX = currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer();
        int tempEndY = currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer();
        col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::ROOM_INTERIOR && col != MapCollisionType::PLATFORM) {
            currentPosition.set_x((currentPosition.x().floor_integer()) - 1);
            collisionContacts[RIGHT_COLLISION] = true;
        }
        else {
            col = MapCollisionType::ROOM_INTERIOR;
        }
    }
    else if(movementDirection.x() < 0) {
        int tempStartX = currentPosition.x().floor_integer();
        int tempStartY = currentPosition.y().floor_integer();
        int tempEndX = currentPosition.x().floor_integer();
        int tempEndY = currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer();
        col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::ROOM_INTERIOR && col != MapCollisionType::PLATFORM) {
            currentPosition.set_x(currentPosition.x().floor_integer() + 1);
            collisionContacts[LEFT_COLLISION] = true;
        }
        else {
            col = MapCollisionType::ROOM_INTERIOR;
        }
    }
    else {
        MapCollisionType tempCol = CheckCollisionWithMapEdge(currentPosition.x().floor_integer() - TILE_WIDTH, currentPosition.y().floor_integer(), 
            currentPosition.x().floor_integer() - TILE_WIDTH, currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer());
        if(tempCol == MapCollisionType::ROOM_INTERIOR || tempCol == MapCollisionType::PLATFORM) {
            collisionContacts[LEFT_COLLISION] = false;

        }
        tempCol = CheckCollisionWithMapEdge(currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer() + TILE_WIDTH, currentPosition.y().floor_integer(), 
            currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer() + TILE_WIDTH, currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer());
        if(tempCol == MapCollisionType::ROOM_INTERIOR || tempCol == MapCollisionType::PLATFORM) {
            collisionContacts[RIGHT_COLLISION] = false;
        }
    }
    return col;
}

MapCollisionType BoxCollision::CheckVerticalCollisions() {
    MapCollisionType col = MapCollisionType::ROOM_INTERIOR;
    // collisionContacts[BOT_COLLISION] = true;
    // return col;
    if(movementDirection.y() > 0) {
        
        int tempStartX = currentPosition.x().floor_integer();
        int tempStartY = currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer();
        int tempEndX = currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer();
        int tempEndY = currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer();
        col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::ROOM_INTERIOR) {
            currentPosition.set_y(currentPosition.y().floor_integer()-1);
            collisionContacts[BOT_COLLISION] = true;
        }        
    }
    else if(movementDirection.y() < 0) {
        int tempStartX = currentPosition.x().floor_integer();
        int tempStartY = currentPosition.y().floor_integer();
        int tempEndX = currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer();
        int tempEndY = currentPosition.y().floor_integer();
        col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::ROOM_INTERIOR && col != MapCollisionType::PLATFORM) {
            currentPosition.set_y(currentPosition.y().floor_integer()+1);
            collisionContacts[TOP_COLLISION] = true;
        }   
        else {
            col = MapCollisionType::ROOM_INTERIOR;
        }
    }
    else {
        if(MapCollisionType::ROOM_INTERIOR == CheckCollisionWithMapEdge(currentPosition.x().floor_integer(), currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer() + TILE_HEIGHT, 
            currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer(), currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer() + TILE_HEIGHT)) {
            collisionContacts[BOT_COLLISION] = false;
        }
    }
    return col;
}

void BoxCollision::CheckCollisionWithMap() {
    int startX = currentPosition.x().floor_integer();
    int startY = currentPosition.y().floor_integer();

    int endX = currentPosition.x().floor_integer() + extension.boxSize.x().floor_integer();
    int endY = currentPosition.y().floor_integer() + extension.boxSize.y().floor_integer();

    MapCollisionType colX = MapCollisionType::COLLISION;
    MapCollisionType colY = MapCollisionType::COLLISION;
    do {
        if(colX != MapCollisionType::ROOM_INTERIOR && colX != MapCollisionType::PLATFORM) {
            colX = CheckHorizontalCollisions();
        }
        if(colY != MapCollisionType::ROOM_INTERIOR) {
            colY = CheckVerticalCollisions();
        }
    } while (colX != MapCollisionType::ROOM_INTERIOR || colY != MapCollisionType::ROOM_INTERIOR);

}