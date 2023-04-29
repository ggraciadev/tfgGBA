#ifndef BF_BASIC_LAYER_H
#define BF_BASIC_LAYER_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/FollowComponent.h"
#include <bn_regular_bg_item.h>
#include <bn_regular_bg_ptr.h>

class BasicLayer : public GameObject {
    public:
    BasicLayer() = default;
    ~BasicLayer() = default;
protected:

    FollowComponent followComponent;
    bn::optional<bn::regular_bg_ptr> background;
public:

    void Start();
    void Update();
    void Render();

    char GetBackgroundLayer();
    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    void SetBackgroundGraphic(const bn::regular_bg_item& bgItem);
};
#endif