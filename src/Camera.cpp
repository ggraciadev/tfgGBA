#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Start() {
    followComponent.SetAlphaOffset(1);
    AddComponent(&followComponent);
    GameObject::Start(); 
}