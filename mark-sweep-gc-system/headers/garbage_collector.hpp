#ifndef _GARBAGE_COLLECTOR_H_
#define _GARBAGE_COLLECTOR_H_
#include "print.hpp"
#include "heap_mapper.hpp"
#include "object.hpp"


//garbage collector class
class GC {
    private:
        HeapInterface& heap_mapper;
        GC(HeapMapper& mapper) : heap_mapper(mapper) {}
        // Delete the copy constructor and assignment operator to prevent copying
        GC(const GC&) = delete;
        GC& operator=(const GC&) = delete;
       

    public:
        static GC& getInstance(HeapMapper& mapper) {
        static GC instance(mapper); // This ensures that only one instance exists
            return instance;
        }
        int garbageCollect();
    
    private:
        void markReachableObjects ();
        //void recMarkReachableObjects(Object *current);
        int sweepUnreachableObjects();
        void recMarkReachableObjects (LinkedListNode<Object **> *current);

};

#endif 
