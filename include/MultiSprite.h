#ifndef BF_MULTI_SPRITE_H
#define BF_MULTI_SPRITE_H

#include "GameObjectComponent.h"
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_sprite_tiles_ptr.h>
#include <bn_sprite_item.h>

template <int tilesX, int tilesY>
class MultiSprite : public GameObjectComponent {
public:
    
    MultiSprite();
    virtual ~MultiSprite();

protected:
    bool flipped;
    bn::vector<bn::optional<bn::sprite_ptr>, tilesX * tilesY> sprites;
    bn::optional<bn::sprite_item> spriteItem;

public:

    virtual void SetSpriteItem(const bn::sprite_item& s);

    virtual void Start() override;
    virtual void Render() override;

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    void SetFlipped(bool flip);
    bool GetFlipped() {return flipped;}
};

template <int tilesX, int tilesY>
MultiSprite<tilesX, tilesY>::MultiSprite() : GameObjectComponent::GameObjectComponent() {

}

template <int tilesX, int tilesY>
MultiSprite<tilesX, tilesY>::~MultiSprite() {

}

template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::Start() {    
    GameObjectComponent::Start();
}

template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::SetSpriteItem(const bn::sprite_item& s){ 
    spriteItem = s; 
    sprites.resize(tilesX * tilesY);
    int index = 0;
    for(int i = 0; i < tilesY; ++i) {
        for(int j = 0; j < tilesX; ++j) {
            sprites[index] = spriteItem->create_sprite(0,0);
            sprites[index]->set_tiles(spriteItem->tiles_item().create_tiles(index));
            index++;
        }
    }
}



template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::Render() {
    GameObjectComponent::Render();

    for(int i = 0; i < tilesY; ++i) {
        for(int j = 0; j < tilesX; ++j) {
            sprites[j + i * tilesX]->set_position(gameObject->GetScreenPosition() + bn::fixed_point(j*64, i*64));
            if(sprites[j + i * tilesX].has_value()) {
            }
        }
    }
}

template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::SetLayerDepth(int depth) {
    for(int i = 0; i < tilesY; ++i) {
        for(int j = 0; j < tilesX; ++j) {
            if(sprites[j + i * tilesX].has_value()) {
                sprites[j + i * tilesX]->set_bg_priority(depth);
            }
        }
    }
}

template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::SetZOrder(char z_order) {
    for(int i = 0; i < tilesY; ++i) {
        for(int j = 0; j < tilesX; ++j) {
            if(sprites[j + i * tilesX].has_value()) {
                sprites[j + i * tilesX]->set_z_order(z_order);
            }
        }
    }
}

template <int tilesX, int tilesY>
void MultiSprite<tilesX, tilesY>::SetFlipped(bool flip) {
    for(int i = 0; i < tilesY; ++i) {
        for(int j = 0; j < tilesX; ++j) {
            if(sprites[j + i * tilesX].has_value()) {
                sprites[j + i * tilesX]->set_horizontal_flip(flip);
            }
        }
    }    
}

#endif