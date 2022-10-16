#include "Scene.h"
#include "bn_keypad.h"

#include "bn_sprite_items_character.h"
#include "bn_sprite_items_bolardo.h"
#include "bn_sprite_items_train.h"

#include "GameManager.h"

Scene::Scene() {

}

Scene::~Scene() {

}


void Scene::Start() {
    parentObject = NestedGameObject(100,0);
    parentObject->SetSprite(bn::sprite_items::character.create_sprite(0, 0));
    object1 = NestedGameObject(-10,0, &(*parentObject));
    object1->SetSprite(bn::sprite_items::bolardo.create_sprite(0, 0));
    object2 = NestedGameObject(0, 10, &(*object1));
    object2->SetSprite(bn::sprite_items::train.create_sprite(0, 0));

    

    //bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));


}

void Scene::Update() {

    if(bn::keypad::left_held())
    {
        parentObject->AddLocalOffset(-1, 0);
    }
    else if(bn::keypad::right_held())
    {
       object1->AddLocalOffset(1, 0);
    }

    if(bn::keypad::up_held())
    {
        parentObject->AddLocalOffset(0, -1);
    }
    else if(bn::keypad::down_held())
    {
        object2->AddLocalOffset(0, 1);
    }

    parentObject->Update();
    object1->Update();
    object2->Update();
}