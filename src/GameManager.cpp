
#include "bn_core.h"
#include "GameManager.h"
#include "bn_string.h"



GameManager* GameManager::instance;

GameManager::GameManager() {
    
}

GameManager::~GameManager() {
    if(scene != nullptr) {
        delete(scene);
    }
}

GameManager* GameManager::GetInstance() {
    if(instance == nullptr) {
        instance = new GameManager();
        instance->Init();
    }
    return instance;
}

void GameManager::Init() {
    scene = new Scene();
    scene->Start();

}

bn::string<64> SetText(bn::sprite_text_generator& t) {
    bn::string<64> string;
    bn::ostringstream string_stream(string);
    int number = 10;
    string_stream << "Text: ";
    string_stream << 123;
    string_stream << " - ";
    string_stream << number;
    return string;
}

void GameManager::Update() {
    scene->Update();
}

void GameManager::Render(bn::sprite_text_generator& t) {
    scene->Render();
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    bn::string<64> string = SetText(t);
    t.generate(0, 0, string, text_sprites);
    bn::core::update();
}

