#include "../headers/heap_mapper.hpp"

void HeapMapper::add_ptr_value(Object **ptr, Object* value)
{
    print("a ptr is: "<<ptr<<" and pointer value is: "<<value);
    m_objects.insert(value);
    updateReferenceTree(ptr);
    m_ptrs.insert(ptr);
    print("=========")

}

void HeapMapper::updateReferenceTree(Object **it) {
    //check if new pointer is already existing, remove the tree to be reassigned
    if (m_address_LLN[it] && m_address_LLN[it]->value){
        deleteRefTree(it);
        print("reassign: "<<it)
    }

    //updating existing reference to reference another object
    if (m_roots.find(it) != m_roots.end()){
        //deleting all references tree of the previous object (no more accessable via this path)
        deleteRefTree(it);
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
        if (*objectRreference == nullptr || **objectRreference == nullptr ){ 
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
                while (current->brother!= nullptr) { current = current->brother; }
                    current->brother = new LinkedListNode<Object **>(it);
                    m_address_LLN[it] = current->brother ; //reference the possible new parent
            }
            print("attached: "<<it << " to: "<< *objectRreference)
            return; //STOP
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
    m_address_LLN[node]->value = nullptr;
}
void HeapMapper::recDeleteRefTree(LinkedListNode<Object**>* current){
    if (!current) return;
    recDeleteRefTree(current->brother);
    recDeleteRefTree(current->child);
    m_ptrs.erase(current->value);
    m_address_LLN.erase(current->value);
    delete current;

}
void HeapMapper::freeHeap() 
{
    for (auto& entry : m_address_LLN) {
        recFreeReferenceTrees(entry.second);
    }
    m_address_LLN.clear(); 
    m_ptrs.clear();
}
void HeapMapper::recFreeReferenceTrees(LinkedListNode<Object **> *node)
{
    if (!node) return;
    recFreeReferenceTrees(node->brother);
    recFreeReferenceTrees(node->child);
    if (node->value) {
        m_ptrs.erase(node->value);
        delete node->value;
        node->value = NULL;
    }
    delete node;
}
inline bool HeapMapper::isInvalidObjectReference(Object **objectRreference)
{
    //check if its null or dangling reference
    return !objectRreference || m_objects.find(*objectRreference) == m_objects.end();
}
