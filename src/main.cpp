#include "bn_core.h"
#include "GameManager.h"


int main()
{
    bn::core::init();

    GameManager* gameManager = GameManager::GetInstance();
    
    bn::sprite_text_generator textGenerator (common::variable_8x16_sprite_font);

    bn::sprite_text_generator* t = &textGenerator;

    textGenerator.set_center_alignment();

    while(true)
    {
        gameManager->Update();
        gameManager->Render(textGenerator);
    }
}
