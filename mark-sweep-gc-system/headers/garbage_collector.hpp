#ifndef _GARBAGE_COLLECTOR_H_
#define _GARBAGE_COLLECTOR_H_

#include "heap_mapper.hpp"

//garbage collector class
class GC {
    private:
        HeapMapper& mapper;
    public:
        GC(HeapMapper& mapper);//: mapper{mapper} {}
        int garbageCollect();

      
    
    private:
        void markReachableObjects ();
        void recMarkReachableObjects(Object *current);
        int sweepUnreachableObjects();
};

#endif 
