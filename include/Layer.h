// #ifndef BF_LAYER_H
// #define BF_LAYER_H

// #include "GameObject.h"

// #include <bn_regular_bg_ptr.h>

// class Layer : public GameObject {
// public:
//     Layer();
//     Layer(const int posX, const int posY, GameObject* _parent = nullptr);
//     virtual ~Layer();

// protected:
//     int layerDepth;
//     bn::fixed layerMovementAlpha;
//     bn::optional<bn::regular_bg_ptr> back;

// public:

//     virtual void Start() override;
//     virtual void Update() override;
//     virtual void Render() override;

//     // virtual bn::fixed_point GetScreenPosition();

//     void SetBackground(bn::regular_bg_ptr b, int layer = 0);
//     virtual void SetLayerDepth(int depth) override;
// };

// #endif