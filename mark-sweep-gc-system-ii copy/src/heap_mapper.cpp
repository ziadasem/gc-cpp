#include "../headers/heap_mapper.hpp"
#include <iostream>
#define print(X) {std::cout << X << std::endl;}

void HeapMapper::add_ptr_value(Object **ptr, Object* value)
{
    print("a ptr is: "<<ptr<<" and pointer value is: "<<value);
    m_objects.insert(value);
    updateReferenceTree(ptr);
    m_ptrs.insert(ptr);
    print("=========")

}

void HeapMapper::updateReferenceTree(Object **it) {
    //updating existing reference to reference another object
    if (m_roots.find(it) != m_roots.end()){
        //deleting all references tree of the previous object (no more accessable via this path)
        recDeleteRefTree(m_roots[it]);
        m_roots[it] = new LinkedListNode<Object **>(it);
        m_address_LLN[it] = m_roots[it] ;
        print("updated: "<<it)
        return;
    }
    //else:
    //check if new reference is accessible by another object (check the address layes in which address range)
    for (auto objectRreference = m_ptrs.begin(); objectRreference != m_ptrs.end(); )
    {
        //check if refernce is valid
        if (*objectRreference == nullptr || **objectRreference == nullptr || (**objectRreference)->integrity != 123456789){ 
            // not valid refernce
            objectRreference = m_ptrs.erase(objectRreference);
            continue;
        }

        //check if new reference is in range in *object reference (accessible by object 'objectRreference')
        if ( it >= reinterpret_cast<void*>(**objectRreference) &&
            it  <= reinterpret_cast<void*>(reinterpret_cast<char*>(**objectRreference) +(**objectRreference)->sizeofclass )) 
        {
            //attach the new reference to its appropriate root
            // if (m_roots.find(*objectRreference) == m_roots.end()){ //object reference is not in roots set
            //     m_roots[*objectRreference] = new LinkedListNode<Object **>(*objectRreference);
            // }
            
            if (m_address_LLN[*objectRreference]->child == nullptr) {
                m_address_LLN[*objectRreference]->child = new LinkedListNode<Object **>(it);
                m_address_LLN[it] = m_address_LLN[*objectRreference]->child; //reference the possible new parent
            }else{
               
                LinkedListNode<Object **>* current = m_address_LLN[*objectRreference]->child;
                 print("Feel the magic in the air")
                while (current->brother!= nullptr) { current = current->brother; }
                    current->brother = new LinkedListNode<Object **>(it);
                    m_address_LLN[it] = current->brother ; //reference the possible new parent
            }
            print("attached: "<<it)
            return; //stop
        }
        objectRreference++ ;
    }
    //else:
    //a new root reference
    m_roots[it] = new LinkedListNode<Object **>(it);
    m_address_LLN[it] = m_roots[it] ;
    print("create: "<<it)
    return;
}
void HeapMapper::deleteRefTree(Object** node){
    recDeleteRefTree(m_address_LLN[node]->child);
    m_address_LLN[node]->child = nullptr;
}
void HeapMapper::recDeleteRefTree(LinkedListNode<Object**>* current){
    if (!current) return;
    recDeleteRefTree(current->brother);
    recDeleteRefTree(current->child);
    m_ptrs.erase(current->value);
    m_address_LLN.erase(current->value);
    delete current;

}
// void HeapMapper::recDeleteRefTree(LinkedListNode<Object**>* current){
//     LinkedListNode<Object **> *temp = current;
//     LinkedListNode<Object **> *tempB = current->brother;
//     LinkedListNode<Object **> *tempC = current->child;
//     while (tempB) {
//         LinkedListNode<Object **> *tempBB = tempB->brother;
//         m_ptrs.erase(tempB->value);
//         m_address_LLN.erase(tempB->value);
//         delete tempB;
//         tempB = tempBB;
//     }
//     while (tempC) {
//         LinkedListNode<Object **> *tempCC = tempC->child;
//         m_ptrs.erase(tempC->value);
//         m_address_LLN.erase(tempC->value);
//         delete tempC;
//         tempC = tempCC;
//     }
//     delete current ;
// }