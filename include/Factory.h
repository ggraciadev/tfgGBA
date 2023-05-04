#ifndef BF_FACTORY_H
#define BF_FACTORY_H

#include "bn_core.h"
#include "bn_vector.h"

template<typename T>
using lent_ptr = T*;


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
        else if(instancesSize < MAX_INSTANCES){
            instances.push_back(T());
            result = &instances[instancesSize];
            instancesSize++;
        }
        else {
            result = nullptr;
        }
        return result;
    }

    void Clear() {
        for(int i = instances.size() - 1; i >= 0; --i) {
            Destroy(&instances[i]);
        }
    }

    void Destroy(T* deletedObject) {
        if(deletedObject != nullptr) {
            freeSpace.push_back(deletedObject);
        }
    }
};


#endif