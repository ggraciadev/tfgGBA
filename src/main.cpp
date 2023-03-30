#include "bn_core.h"
#include "bn_unique_ptr.h"
#include "GameManager.h"


int main()
{
    bn::core::init();
    GameManager* gm = GameManager::GetInstance();

    //GameManager* gameManager = GameManager::GetInstance();
    
    bn::sprite_text_generator textGenerator (common::variable_8x16_sprite_font);

    textGenerator.set_center_alignment();
    
    while(true)
    {
        gm->Update();
        gm->PhysicsUpdate();
        gm->Render(textGenerator);
        //bn::core::update();
    }
}
