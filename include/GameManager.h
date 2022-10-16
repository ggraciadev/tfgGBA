#ifndef BF_GAME_MANAGER_H
#define BF_GAME_MANAGER_H

#include "bn_core.h"
#include "bn_optional.h"
#include "Scene.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

class GameManager { //Singleton

protected:

    GameManager();
    static GameManager* instance;
    Scene scene;

    bn::sprite_text_generator* textGen;


public:
    ~GameManager();
    static GameManager* GetInstance();

    void Init();

    void Update(bn::sprite_text_generator& t);


};

#endif