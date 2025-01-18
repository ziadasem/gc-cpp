
#include "../headers/garbage_collector.hpp"
#define Number_Of_Sweeped_Objects int

#include <thread>
#include <chrono>
#include <iostream>

Number_Of_Sweeped_Objects GC::garbageCollect(){
    print("number of ptrs: "<<heap_mapper.m_ptrs.size());
    print("number of objects: "<< heap_mapper.m_objects.size());
    print("number of roots: "<< heap_mapper.m_roots.size());
    markReachableObjects();
    return sweepUnreachableObjects();
}


void GC::markReachableObjects (){
    
    for (auto it = heap_mapper.m_roots.begin(); it != heap_mapper.m_roots.end(); ) {
        if (heap_mapper.isInvalidObjectReference(it->second->value) ) {
            // Remove the key when the reference is invalid
            it = heap_mapper.m_roots.erase(it);
        } else {
            if (*(it->first) == nullptr) {
                heap_mapper.deleteRefTree(it->first);
                it = heap_mapper.m_roots.erase(it); // Remove key after deleting reference tree
            } else {
                recMarkReachableObjects(it->second); // Find its children
                ++it;
            }
        }
}
    
}

void GC::recMarkReachableObjects (LinkedListNode<Object **> *current){
    
    if (current == nullptr) return ;
    if (!current->value){ 
        recMarkReachableObjects(current->brother);
        return ;
    }     
   if (*current->value){
        if ((*current->value)->mark_bit){ return ;} //avoid infinite recursion
        
        (*current->value)->mark_bit = true ;
   }else{
        heap_mapper.deleteRefTree(current->value); //delete the reference tree
        recMarkReachableObjects(current->brother);
        return ;
   }
   recMarkReachableObjects(current->brother);
   recMarkReachableObjects(current->child);
  
}


int GC::sweepUnreachableObjects(){
    int freedCount = 0;

    for (auto it = heap_mapper.m_objects.begin(); it != heap_mapper.m_objects.end(); ){
        if (!(*it)->mark_bit) { 
            //(*it)->integrity = 0;        
            delete *it;
            freedCount++;
            it = heap_mapper.m_objects.erase(it);
        }else{
            (*it)->mark_bit = false;
            ++it ;
        }
       
    }
    return freedCount;
}



