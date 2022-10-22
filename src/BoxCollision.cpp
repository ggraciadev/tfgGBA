#include "BoxCollision.h"
#include "MapCollision.h"
#include "GameObject.h"

BoxCollision::BoxCollision() : GameObjectComponent::GameObjectComponent(){

}

BoxCollision::~BoxCollision() {

}

void BoxCollision::Setup(bn::fixed_point offset, bn::fixed_point size) {
    boxOffset = offset;
    boxSize = size;
}

void BoxCollision::Setup(int offX, int offY, int width, int height) {
    Setup(bn::fixed_point(offX, offY), bn::fixed_point(width, height));
}

void BoxCollision::Start() {
    GameObjectComponent::Start();
    currentPosition = gameObject->GetWorldPosition();
}

void BoxCollision::Update() {
    updatedPosition = false;
    lastPosition = currentPosition;
    GameObjectComponent::Update();
}

void BoxCollision::PhysicsUpdate() {
    if(!updatedPosition) {
        UpdateCurrentPosition();
    }
    if(mapCollision != nullptr) {
        CheckCollisionWithMap();
        UpdateContacts();
        gameObject->SetLocalPosition(currentPosition);
    
    }
}

void BoxCollision::UpdateCurrentPosition() {
    currentPosition = gameObject->GetWorldPosition() + boxOffset;
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
            currentPosition.x() + boxSize.x() > otherPosition.x() &&
            currentPosition.y() < otherPosition.y() + otherSize.y() &&
            currentPosition.y() + boxSize.y() > otherPosition.y();
}

MapCollisionType BoxCollision::CheckCollisionWithMapEdge(int startX, int startY, int endX, int endY) {
    MapCollisionType result = MapCollisionType::NONE;
    for(int i = startY; i < endY+1 && result == MapCollisionType::NONE; i += TILE_HEIGHT) {
        for(int j = startX; j < endX+1 && result == MapCollisionType::NONE; j += TILE_WIDTH) {
            result = mapCollision->GetCollisionByPosition(j, i);
        }
    }

    return result;
}

void BoxCollision::UpdateContacts() {
    bn::fixed_point movement = currentPosition - lastPosition;

    if(movement.x() > 0) {
        collisionContacts[LEFT_COLLISION] = false;
    }
    else if(movement.x() < 0) {
        collisionContacts[RIGHT_COLLISION] = false;
    }

    if(movement.y() > 0) {
        collisionContacts[TOP_COLLISION] = false;
    }
    else if(movement.y() < 0) {
        collisionContacts[BOT_COLLISION] = false;
    }
}

void BoxCollision::CheckCollisionWithMap() {
    bn::fixed_point movement = currentPosition - lastPosition;
    int startX = currentPosition.x().floor_integer();
    int startY = currentPosition.y().floor_integer();

    int endX = currentPosition.x().floor_integer() + boxSize.x().floor_integer();
    int endY = currentPosition.y().floor_integer() + boxSize.y().floor_integer();

    if(movement.x() > 0) {
        int tempStartX = endX;
        int tempStartY = startY;
        int tempEndX = endX;
        int tempEndY = endY;
        MapCollisionType col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::NONE) {
            currentPosition.set_x(currentPosition.x().floor_integer() / TILE_WIDTH * TILE_WIDTH);
            collisionContacts[RIGHT_COLLISION] = true;
        }
    }
    else if(movement.x() < 0) {
        int tempStartX = startX;
        int tempStartY = startY;
        int tempEndX = startX;
        int tempEndY = endY;
        MapCollisionType col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::NONE) {
            currentPosition.set_x(currentPosition.x().floor_integer() / TILE_WIDTH * TILE_WIDTH + TILE_WIDTH);
            collisionContacts[LEFT_COLLISION] = true;
        }
    }

    if(movement.y() > 0) {
        
        MapCollisionType col;
        do {
            int tempStartX = currentPosition.x().floor_integer();
            int tempStartY = currentPosition.y().floor_integer() + boxSize.y().floor_integer();
            int tempEndX = currentPosition.x().floor_integer() + boxSize.x().floor_integer();
            int tempEndY = currentPosition.y().floor_integer() + boxSize.y().floor_integer();
            col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
            if(col != MapCollisionType::NONE) {
                currentPosition.set_y(currentPosition.y().floor_integer() / TILE_HEIGHT * TILE_HEIGHT);
                collisionContacts[BOT_COLLISION] = true;
            }
        } while (col != MapCollisionType::NONE);
    }
    else if(movement.y() < 0) {
        int tempStartX = startX;
        int tempStartY = endY;
        int tempEndX = endX;
        int tempEndY = endY;
        MapCollisionType col = CheckCollisionWithMapEdge(tempStartX, tempStartY, tempEndX, tempEndY);
        if(col != MapCollisionType::NONE) {
            currentPosition.set_y(currentPosition.y().floor_integer() / TILE_HEIGHT * TILE_HEIGHT);
            collisionContacts[TOP_COLLISION] = true;
        }
    }
}