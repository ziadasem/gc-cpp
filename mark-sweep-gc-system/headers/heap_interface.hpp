#ifndef __HEAP_Interface__H_

#define __HEAP_Interface__H_
#include "object.hpp"
#include <set>
#include <map>

class Object;

template<class T>
class LinkedListNode {
    public:
     LinkedListNode* brother ;
     LinkedListNode* child ;
     T value ;
     LinkedListNode( T value, LinkedListNode* brother = nullptr, LinkedListNode* child  = nullptr): 
     brother(brother), child(child), value(value) {}
};

class HeapInterface {
    friend class GC ;
    protected:  
        std::set<Object**> m_ptrs ;
        std::set<Object*> m_objects ;
        std::map<Object**,  LinkedListNode<Object**>*> m_roots ;
    public:
  
    virtual void add_ptr_value(Object **ptr, Object* value) =0;
    virtual void deleteRefTree(Object**) = 0;

    inline virtual bool isDanglingObjectReference(Object**) = 0 ;
    private:   
};

#endif // !__HEAP_Interface__H_

