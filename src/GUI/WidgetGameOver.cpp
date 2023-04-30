#include "GUI/WidgetGameOver.h"
#include "GameManager.h"


void WidgetGameOver::Start() {
    GUIWidget::Start();
    InitMenu();
}

void WidgetGameOver::InitMenu() {
    SetEnabled(true);
    
    playAgainButton.Start();
    playAgainButton.SetParent(this);
    playAgainButton.SetRelativePosition(bn::fixed_point(-58,-4));
    playAgainButton.SetEnabled(true);

    goToMainMenuButton.Start();
    goToMainMenuButton.SetParent(this);
    goToMainMenuButton.SetRelativePosition(bn::fixed_point(-58,44));
    goToMainMenuButton.SetEnabled(true);

    maxItems = 2;

    SetCurrentButtonSelected(0);
}

void WidgetGameOver::Render() {
    playAgainButton.Render();
    goToMainMenuButton.Render();
}

void WidgetGameOver::SetCurrentButtonSelected(int selected) {
    playAgainButton.SetSelected(selected == 0);
    goToMainMenuButton.SetSelected(selected == 1);
    WidgetMenu::SetCurrentButtonSelected(selected);
}

void WidgetGameOver::OnClickPlayAgain() {
    GameManager::GetInstance()->PlayGame();
}

void WidgetGameOver::OnClickGoToMainMenu() {
    GameManager::GetInstance()->ChangeScene(GameScenes::SCENE_MAIN_MENU);
}

void WidgetGameOver::OnClick() {
    if(currentSelected == 0) {
        OnClickPlayAgain();
    }
    else {
        OnClickGoToMainMenu();
    }
}