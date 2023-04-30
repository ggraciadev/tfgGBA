#ifndef BF_INTERACTUABLE_H
#define BF_INTERACTUABLE_H

#include "GameObjects/GameObject.h"
#include "GUI/GUIWorldSpace.h"
#include "GameObjectComponents/BoxCollision.h"

class Player;

class Interactuable : public GameObject {
public:

    Interactuable() = default;
    ~Interactuable() = default;

protected:
    GUIWorldSpace interactivePrompt;
    Player* player;
    BoxCollision boxCollision;

    bn::fixed_point promptOffset;

    bn::optional<bn::sprite_ptr> sprite;

    bool playerTriggered;

public:
    virtual void Start();
    virtual void Update() override;
    virtual void Render() override;
    virtual void SetCamera(GameObject* cam) override;

    virtual void InitPrompt();
    virtual void InitSprite(const bn::sprite_item& item);
    void SetGraphic(HUDGraphics graphic) { interactivePrompt.SetGraphic(graphic); }

    inline void SetPlayer(Player* p) { player = p; }
    void OnPlayerTriggerEnter();
    void OnPlayerTriggerExit();

    virtual void Interact();
    void SetGraphicEnabled(bool enabled);


};

#endif