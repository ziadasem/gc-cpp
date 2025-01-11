#ifndef _GARBAGE_COLLECTOR_H_
#define _GARBAGE_COLLECTOR_H_

#include "heap_mapper.hpp"
#include "object.hpp"
#include <map>

template<class T>
class LinkedListNode {
    public:
     LinkedListNode* brother ;
     LinkedListNode* child ;
     T value ;
     LinkedListNode( T value, LinkedListNode* brother = nullptr, LinkedListNode* child  = nullptr): 
     brother(brother), child(child), value(value) {}
};


//garbage collector class
class GC {
    private:
        HeapInterface& heap_mapper;
        GC(HeapMapper& mapper) : heap_mapper(mapper) {}
        // Delete the copy constructor and assignment operator to prevent copying
        GC(const GC&) = delete;
        GC& operator=(const GC&) = delete;
        std::map<Object**,  LinkedListNode<Object**>*> m_roots ;
        std::set< LinkedListNode<Object**>*> m_root_roots ;


    public:
        static GC& getInstance(HeapMapper& mapper) {
        static GC instance(mapper); // This ensures that only one instance exists
            return instance;
        }
        int garbageCollect();
    
    private:
        void markReachableObjects ();
        void recMarkReachableObjects(Object *current);
        int sweepUnreachableObjects();
        void recMarkReachableObjects (LinkedListNode<Object **> *current);

        void buildReferenceTree();
        void freeGCMemory();
};

#endif 
