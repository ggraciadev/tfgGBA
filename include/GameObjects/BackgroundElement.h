#ifndef BF_BACKGROUND_ELEMENT_H
#define BF_BACKGROUND_ELEMENT_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/MultiSprite.h"

template <int tilesX, int tilesY>
class BackgroundElement : public GameObject {
public:
    BackgroundElement();
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);
    virtual ~BackgroundElement();

protected:

    MultiSprite<tilesX, tilesY> multiSprite;

public:
    void Start();
    virtual void Update();

    void SetSpriteItem(const bn::sprite_item& s);

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);
    void SetFlipped(bool flip) { multiSprite.SetFlipped(flip); }

};

template <int tilesX, int tilesY>
BackgroundElement<tilesX, tilesY>::BackgroundElement() : GameObject() {

}

template <int tilesX, int tilesY>
BackgroundElement<tilesX, tilesY>::~BackgroundElement() {
    
}


template <int tilesX, int tilesY>
void BackgroundElement<tilesX, tilesY>::Start() {
    AddComponent(&multiSprite);
    GameObject::Start();
}

template <int tilesX, int tilesY>
void BackgroundElement<tilesX, tilesY>::Update() {
    GameObject::Update();
}

template <int tilesX, int tilesY>
void BackgroundElement<tilesX, tilesY>::SetSpriteItem(const bn::sprite_item& s) { 
    multiSprite.SetSpriteItem(s); 
}

template <int tilesX, int tilesY>
void BackgroundElement<tilesX, tilesY>::SetLayerDepth(int depth) {
    GameObject::SetLayerDepth(depth);
    multiSprite.SetLayerDepth(data.layerDepth);
}

template <int tilesX, int tilesY>
void BackgroundElement<tilesX, tilesY>::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    multiSprite.SetZOrder(data.zOrder);
}

#endif