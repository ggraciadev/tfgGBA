#include "Scenes/Scene.h"
#include "GameManager.h"


void Scene::Start() {
    
}

void Scene::Update() {
    for(int i = 0; i < gameObjects.size(); ++i) {
        if(gameObjects[i] != nullptr) {
            gameObjects[i]->Update();
        }
    }
}

void Scene::PhysicsUpdate() {
    for(int i = 0; i < gameObjects.size(); ++i) {
        if(gameObjects[i] != nullptr) {
            gameObjects[i]->PhysicsUpdate();
        }
    }
}

void Scene::Render() {
    for(int i = 0; i < gameObjects.size(); ++i) {
        if(gameObjects[i] != nullptr) {
            gameObjects[i]->Render();
        }
    }
}