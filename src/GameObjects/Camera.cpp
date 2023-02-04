#include "GameObjects/Camera.h"

void Camera::Start() {
    followComponent.SetAlphaOffset(1);
    AddComponent(&followComponent);
    GameObject::Start(); 
}