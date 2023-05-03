#ifndef BF_PLAYER_H
#define BF_PLAYER_H

#include "GameObjects/Character.h"
#include "GameObjectComponents/Animator.h"
#include "GameObjectComponents/InputComponent.h"
#include "GameObjectComponents/JumpAbility.h"
#include "GameObjectComponents/MeleeComboAbility.h"
#include "GUI/WidgetHUD.h"

class Interactuable;

class Player : public Character {

public:
    Player() = default;
    ~Player() = default;

protected:

    InputComponent input;
    JumpAbility jumpAb; 
    MeleeComboAbility<3> meleeComboAb;
    Animator<4, 16> animator;
    
    WidgetHUD* widgetHUD;

    Interactuable* currentInteractuable;

    virtual void SetupAnimations();
    virtual void SetupAttacks();

    virtual void SetAtkPowerUp(bool powUp);
    virtual void SetDefPowerUp(bool powUp);


public:
    inline void SetHUD(WidgetHUD* hud) { widgetHUD = hud; }

    virtual void Start();
    virtual void Update();

    void Jump();
    void Attack();
    void Dash();

    virtual void Die() override;

    void UpdateAnimationState();

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    virtual bool GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition);

    void SetCurrentInteractuable(Interactuable* value, Interactuable* requested);
};

#endif