#include "Scenes/MainMenuScene.h"

#include "bn_regular_bg_items_main_menu.h"
#include "GameManager.h"

#include "bn_keypad.h"

void MainMenuScene::Start() {
    background.SetBackgroundGraphic(bn::regular_bg_items::main_menu);
    background.SetLayerDepth(3);
    background.SetZOrder(5);
    background.Start();

    widgetMainMenu.Start();

}

void MainMenuScene::Update() {
    if(bn::keypad::a_pressed()) {
        widgetMainMenu.OnClick();
    }
}

void MainMenuScene::Render() {
    background.Render();
}