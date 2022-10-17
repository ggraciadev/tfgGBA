#ifndef BF_FACTORY_H
#define BF_FACTORY_H

#include "bn_core.h"
#include "bn_vector.h"

#define MAX_INSTANCES 1024

template <class T>
class Factory {
public:
    Factory() {
        instancesSize = 0;
    }
    ~Factory() {

    }

protected:

    bn::vector<T, MAX_INSTANCES> instances;
    int instancesSize;

public:
    
    T* Create() {
        instances.push_back(T());
        T* result = &instances[instancesSize];
        instancesSize++;
        return result;
    }
};


#endif