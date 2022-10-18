#ifndef BF_FACTORY_H
#define BF_FACTORY_H

#include "bn_core.h"
#include "bn_vector.h"


template <class T, int MAX_INSTANCES>
class Factory {
public:
    Factory() {
        instancesSize = 0;
    }
    ~Factory() {

    }

protected:

    bn::vector<T, MAX_INSTANCES> instances;
    bn::vector<T*, MAX_INSTANCES> freeSpace;
    int instancesSize;

public:
    
    T* Create() {

        T* result;

        if(freeSpace.size() > 0) {
            result = freeSpace[freeSpace.size() - 1];
            freeSpace.pop_back();
        }
        else {
            instances.push_back(T());
            result = &instances[instancesSize];
            instancesSize++;
        }
        return result;
    }

    void Destroy(T* deletedObject) {
        if(deletedObject != nullptr) {
            freeSpace.push_back(deletedObject);
        }
    }
};


#endif