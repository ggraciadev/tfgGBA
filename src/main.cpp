#include "bn_core.h"
#include "bn_keypad.h"
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_tiles_ptr.h>

#include "bn_sprite_items_main_character.h"
#include "bn_sprite_items_bolardo.h"
#include "bn_sprite_items_farola.h"
#include "bn_regular_bg_items_back.h"


int main()
{
    bn::core::init();
    int posX = 0;
    int posY = 50;
    bn::sprite_ptr sprite = bn::sprite_items::main_character.create_sprite(posX, posY);
    sprite.set_z_order(0);
    
    bn::sprite_ptr farola1 = bn::sprite_items::farola.create_sprite(-50, 0);
    bn::sprite_ptr farola2 = bn::sprite_items::farola.create_sprite(-50, 64);

    bn::sprite_ptr bolardo = bn::sprite_items::bolardo.create_sprite(20, 60);

    bn::regular_bg_ptr back = bn::regular_bg_items::back.create_bg(10, 50);

    farola2.set_tiles(bn::sprite_items::farola.tiles_item().create_tiles(1));
          

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
        }
        sprite.set_x(posX);
        sprite.set_y(posY);

        bn::core::update();
    }
}
