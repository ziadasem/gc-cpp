
#include "../headers/garbage_collector.hpp"
#define Number_Of_Sweeped_Objects int

Number_Of_Sweeped_Objects GC::garbageCollect(){
    markReachableObjects();
    return sweepUnreachableObjects();
}

void GC::markReachableObjects (){
    //start with root set
    for (auto it : heap_mapper.m_ptr_value) {
        recMarkReachableObjects((Object  *) it.second);
    }
    
}

void GC::recMarkReachableObjects (Object* current) {
   
}
int GC::sweepUnreachableObjects(){
     int freedCount = 0;
    
     return freedCount;
}
