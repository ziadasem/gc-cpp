
#include "../headers/garbage_collector.hpp"
#define Number_Of_Sweeped_Objects int

#include <iostream>
#define print(X) {std::cout << X << std::endl;}

Number_Of_Sweeped_Objects GC::garbageCollect(){
    print("number of ptrs: "<<heap_mapper.m_ptrs.size());
    print("number of objects: "<< heap_mapper.m_objects.size());
   
    buildReferenceTree();
    print("number of root root: "<< m_root_roots.size());
    markReachableObjects();
    return sweepUnreachableObjects();
}

void GC::buildReferenceTree() {
    bool isRoot = true;
    for (auto it = heap_mapper.m_ptrs.begin(); it != heap_mapper.m_ptrs.end(); ) {
        
           isRoot = true ;
           for (auto it2 = std::next(it); it2 != heap_mapper.m_ptrs.end(); ) {
                if (*it2 == *it) { it2++ ; continue; }
                //check if refernce is valid
                if (*it2 == nullptr || **it2 == nullptr || (**it2)->integrity != 123456789){ 
                    // not valid refernce
                    it2 = heap_mapper.m_ptrs.erase(it2);
                    continue;
                }
                //check if *it1 is in range in *it2
                if ( *it >= reinterpret_cast<void*>(**it2) &&
                    *it  < reinterpret_cast<void*>
                        (
                        reinterpret_cast<char*>(**it2) + sizeof(**it2)
                        )
                    ) {
                        if (m_roots.find(*it2) == m_roots.end()){
                            m_roots[*it2] = new LinkedListNode<Object **>(*it2);
                        }
                        if (m_roots[*it2]->child == nullptr) {
                            m_roots[*it2]->child = new LinkedListNode<Object **>(*it);
                        }else{
                            LinkedListNode<Object **>* current = m_roots[*it2]->child;
                            while (current->brother!= nullptr) { current = current->brother; }
                            current->brother = new LinkedListNode<Object **>(*it);
                        }
                        isRoot = false ;
                        break ;
                    }
                
                    it2++ ;
           }
           if (isRoot){
                m_root_roots.insert(new LinkedListNode<Object**>(*it));
           }
           it ++ ;
    }

}

void GC::markReachableObjects (){
    for (auto it : m_root_roots){
        recMarkReachableObjects(it); //find its children
    }
}

void GC::recMarkReachableObjects (LinkedListNode<Object **> *current){
   if (current == nullptr) return ;

   if (*current->value){
    (*current->value)->mark_bit = true ;
   }
   LinkedListNode<Object **> *tempB = current->brother;
   while (tempB){
    (*tempB->value)->mark_bit = true ;  
    recMarkReachableObjects(tempB->brother); //find its brother
    recMarkReachableObjects(tempB->child); //find its children
   }

   LinkedListNode<Object **> *tempC = current->child;
   while (tempC){
    (*tempC->value)->mark_bit = true ;  
    recMarkReachableObjects(tempC->brother); //find its brother
    recMarkReachableObjects(tempC->child); //find its children
   }
}

int GC::sweepUnreachableObjects(){
    int freedCount = 0;
    for (auto it : heap_mapper.m_objects){
       
        if (!it->mark_bit) {
            print(it)
            delete it;
            freedCount++;
        }else{
            it->mark_bit = false;
        }
       
    }
    return freedCount;
}



