#include "bn_core.h"
#include "bn_keypad.h"
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_character.h"
#include "bn_sprite_items_cobblestone.h"


int main()
{
    bn::core::init();
    int posX = 0;
    int posY = 0;
    bn::sprite_ptr sprite = bn::sprite_items::character.create_sprite(posX, posY);

    bn::sprite_ptr ground = bn::sprite_items::cobblestone.create_sprite(1 << -1, 15);

    while(true)
    {
        if(bn::keypad::left_held())
        {
            --posX;
        }
        else if(bn::keypad::right_held())
        {
            ++posX;
        }
        if(bn::keypad::up_held())
        {
            --posY;
        }
        else if(bn::keypad::down_held())
        {
            ++posY;
            if(posY > 15 - 32 - 8) {
                posY = 15 - 32 - 8;
            }
        }
        sprite.set_x(posX);
        sprite.set_y(posY);

        bn::core::update();
    }
}
