#include "../headers/heap_mapper.hpp"
#include <iostream>
#define print(X) {std::cout << X << std::endl;}

void HeapMapper::add_ptr_value(Object **ptr, Object* value)
{
    print(ptr);
    print(value);
    print("=========")
    m_ptrs.insert(ptr);
    m_objects.insert(value);

}
void HeapMapper::addObject(Object* value)
{
    m_objects.insert((Object *) value);
}

void HeapMapper::addPtr(Object*& value){
    // bool is_root = true ;
    // for (auto it = m_ptrs.begin(); it != m_ptrs.end(); ) {
    //     if (*it == nullptr) { 
    //         it = m_ptrs.erase(it); 
    //     } else { 
    //         if ( (*it)->getIntegrity() == 123456789){
    //             void* basePtr = &value ;
    //             if (basePtr >= reinterpret_cast<void*>(*it) &&
    //                 basePtr < 
    //                 reinterpret_cast<void*>(reinterpret_cast<char*>(*it) 
    //                 + sizeof(**it)
    //                )
    //             ) 
    //             {
    //                 if ( (*it)->child){
    //                     Object ** temp =  (*it)->child ;
    //                     while( (*temp)->brother){
    //                         temp = temp->bro ;
    //                     }
    //                 }else{
    //                     (*it)->child = (Object **) basePtr ;
    //                 }
    //                 break ;
    //             }
                
    //             ++it; 
    //         }else{
    //             it = m_ptrs.erase(it); 
    //         }
            
    //     }
    // }
    // m_ptrs.insert(value);
}

