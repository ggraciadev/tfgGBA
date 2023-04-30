#include "Scenes/GameOverScene.h"

#include "bn_regular_bg_items_game_over.h"
#include "GameManager.h"

#include "bn_keypad.h"

void GameOverScene::Start() {
    background.SetBackgroundGraphic(bn::regular_bg_items::game_over);
    background.SetLayerDepth(3);
    background.SetZOrder(5);
    background.Start();

    widgetGameOver.Start();

}

void GameOverScene::Update() {
    if(bn::keypad::a_pressed()) {
        widgetGameOver.OnClick();
    }
    else if(bn::keypad::down_pressed()) {
        widgetGameOver.NextButton();
    }
    else if(bn::keypad::up_pressed()) {
        widgetGameOver.PrevButton();
    }
}

void GameOverScene::Render() {
    background.Render();
}