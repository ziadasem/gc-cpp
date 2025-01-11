#ifndef __HEAP_Interface__H_

#define __HEAP_Interface__H_
#include "object.hpp"
#include <set>
//#include <unordered_map>
class Object;



class HeapInterface {
    friend class GC ;
    protected:  
        std::set<Object**> m_ptrs ;
        std::set<Object*> m_objects ;
        
    public:
  
    virtual void add_ptr_value(Object **ptr, Object* value) =0;

    // Public methods for manipulating the unordered_map and unordered_set
    virtual void addObject( Object* value) = 0 ;
    private:   
};

#endif // !__HEAP_Interface__H_

