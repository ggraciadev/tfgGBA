#include "Camera.h"

Camera::Camera() : GameObject() {
    followObject = nullptr;
}

Camera::~Camera() {

}

void Camera::Start() {
    
}

void Camera::Update() {
    if(followObject != nullptr) {
        SetLocalPosition(followObject->GetWorldPosition());
    }
}

void Camera::Render() {
    
}

void Camera::SetFollowObject(GameObject* _followObject) {
    followObject = _followObject;
}