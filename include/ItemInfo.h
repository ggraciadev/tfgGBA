#ifndef BF_ITEM_INFO_H
#define BF_ITEM_INFO_H

#include "bn_string.h"



class ItemInfo {

public: 
    ItemInfo() = default;
    ~ItemInfo() = default;

protected:
    bn::string<16> name;
    bn::string<128> description;

public:

    inline void SetName(bn::string<16> n) { name = n; }
    inline bn::string<16> GetName() const { return name; }

    inline void SetDescription(bn::string<128> d) { description = d; }
    inline bn::string<128> GetDescription() const { return description;; }

};

#endif