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

};

#endif