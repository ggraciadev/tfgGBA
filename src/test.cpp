#include "bn_core.h"
#include "bn_keypad.h"
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_tiles_ptr.h>

#include "bn_bg_palettes.h"
#include "bn_sprite_palette_actions.h"
#include "bn_sprite_palettes_actions.h"

#include "bn_sprite_items_character.h"
#include "bn_sprite_items_house.h"
#include "bn_sprite_items_bolardo.h"
#include "bn_sprite_items_train.h"
#include "bn_sprite_items_farola.h"
#include "bn_regular_bg_items_back.h"
#include "bn_sprite_palette_items_main_character_palette.h"

#include <bn_array.h>
#include <bn_optional.h>



int mainFoo()
{
    bn::core::init();
    int posX = 0;
    int posY = 50;

    bn::regular_bg_ptr back = bn::regular_bg_items::back.create_bg(10, 50);

    bn::sprite_ptr sprite = bn::sprite_items::character.create_sprite(posX, posY);

    // bn::array<bn::optional<bn::sprite_ptr>,123> spriteList;

    // for(int i = 0; i < 123; ++i) {
    //     spriteList[i] = bn::sprite_items::character.create_sprite(-128 + (i%20) * 64, - 40 + i / 20 * 50);
    //     (*spriteList[i]).set_bg_priority(1);
    //     (*spriteList[i]).set_z_order(0);
    // }
    
    //bn::sprite_ptr sprite = bn::sprite_items::character.create_sprite(posX, posY);

    // const bn::sprite_palette_item& character_palette_colors = bn::sprite_palette_items::main_character_palette;
    // bn::sprite_palette_ptr character_palette = (*sprite).palette();
    // character_palette.set_colors(character_palette_colors);
          
    bn::sprite_ptr farola1 = bn::sprite_items::farola.create_sprite(40, 0);
    bn::sprite_ptr farola2 = bn::sprite_items::farola.create_sprite(40, 64);
    farola2.set_tiles(bn::sprite_items::farola.tiles_item().create_tiles(1));
    bn::sprite_ptr bolardo = bn::sprite_items::bolardo.create_sprite(-50, 70);

    back.set_priority(3);
    sprite.set_bg_priority(0);
    farola1.set_bg_priority(0);
    farola2.set_bg_priority(0);
    
    bolardo.set_bg_priority(0);

    sprite.set_z_order(1);
    farola1.set_z_order(0);
    farola2.set_z_order(0);
    bolardo.set_z_order(0);


    bn::sprite_ptr train = bn::sprite_items::train.create_sprite(-50, -25);
    train.set_bg_priority(3);
    int direction = 0;

    

    while(true)
    {
        direction = 0;
        if(bn::keypad::left_held())
        {
            direction = -1;
        }
        else if(bn::keypad::right_held())
        {
            direction = 1;
        }
        if(bn::keypad::up_held())
        {
            --posY;
        }
        else if(bn::keypad::down_held())
        {
            ++posY;
        }

        if(direction == 1 && sprite.horizontal_flip()) {
            sprite.set_horizontal_flip(false);
        }
        else if(direction == -1 && !sprite.horizontal_flip()) {
            sprite.set_horizontal_flip(true);
        }

        posX += direction;

        sprite.set_x(posX);
        sprite.set_y(posY);

        bn::core::update();
    }
}
