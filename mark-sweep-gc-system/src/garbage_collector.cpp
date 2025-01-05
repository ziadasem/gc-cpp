
#include "../headers/garbage_collector.hpp"

GC::GC(HeapMapper& mapper): mapper{mapper} {}

int GC::garbageCollect(){
     markReachableObjects();  
     return sweepUnreachableObjects();     
}

void GC::markReachableObjects (){
     auto* rootSetPtr = static_cast<std::unordered_set<Object*>*>(mapper.get_root_set());
     for (auto root: *rootSetPtr){
          recMarkReachableObjects(root);
     }
}

void GC::recMarkReachableObjects (Object* current) {
     if (!current){
          return ;
     }
     if (current->mark_bit){ //prevent infinite recursion, in case of graph
          return ;
     }
     current->mark_bit = true ; //freind access, only for GC class
     for (auto& child : current->m_references){
          recMarkReachableObjects(child);
     }
}
int GC::sweepUnreachableObjects(){
     int freedCount = 0;
     auto* rootSetPtr = static_cast< std::unordered_set<Object*>*>(mapper.get_object_address());
     for (auto obj: *rootSetPtr){
          if (obj->mark_bit){
               obj->mark_bit = false;
          }else{
               //free memory
               delete obj;
               obj = nullptr;
               freedCount ++ ;
          }
          
     }
     return freedCount;
}
