#ifndef __HEAP_Interface__H_

#define __HEAP_Interface__H_

#include <unordered_set>
#include <unordered_map>

class HeapInterface {
    friend class GC ;
    protected:  
        // Private constructor to prevent instantiation
        std::unordered_map<void*, void*> m_ptr_value ;
        std::unordered_set<void*> m_objects ;

    public:
  
    // Public methods for manipulating the unordered_map and unordered_set
    virtual void addRootObject(void* key, void* value) = 0 ;
    virtual void addObject(void* value) = 0 ;

    virtual void removeRootVaraible(void* key) = 0;
    virtual bool containsObject(void* key) = 0 ;
    private:   
};

#endif // !__HEAP_Interface__H_

