#include "GUI/WidgetMenu.h"
#include "GameManager.h"


void WidgetMenu::Start() {
    GUIWidget::Start();
    InitMenu();
}

void WidgetMenu::InitMenu() {
    SetEnabled(true);
    SetCurrentButtonSelected(0);
}

void WidgetMenu::SetCurrentButtonSelected(int selected) {
    currentSelected = selected;
    Render();
}

void WidgetMenu::NextButton() {
    int temp = currentSelected + 1;
    if(temp >= maxItems) {
        temp = 0;
    }
    SetCurrentButtonSelected(temp);
}

void WidgetMenu::PrevButton() {
    int temp = currentSelected - 1;
    if(temp < 0) {
        temp = maxItems-1;
    }
    SetCurrentButtonSelected(temp);
}