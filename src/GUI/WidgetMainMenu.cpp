#include "GUI/WidgetMainMenu.h"
#include "GameManager.h"


void WidgetMainMenu::Start() {
    GUIWidget::Start();
    InitMenu();
}

void WidgetMainMenu::InitMenu() {
    SetEnabled(true);
    
    playButton.Start();
    playButton.SetParent(this);
    playButton.SetRelativePosition(bn::fixed_point(-58,44));
    playButton.SetEnabled(true);

    maxItems = 1;

    SetCurrentButtonSelected(0);
}

void WidgetMainMenu::Render() {
    playButton.Render();
}

void WidgetMainMenu::SetCurrentButtonSelected(int selected) {
    playButton.SetSelected(true);
    WidgetMenu::SetCurrentButtonSelected(selected);
}

void WidgetMainMenu::OnClickPlay() {
    GameManager::GetInstance()->PlayGame();
}

void WidgetMainMenu::OnClick() {
    OnClickPlay();
}