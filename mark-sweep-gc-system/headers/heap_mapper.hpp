#ifndef __HEAP_MAPPER__H_

#define __HEAP_MAPPER__H_

#include "heap_interface.hpp"
#include <map>


class HeapMapper : public HeapInterface {
    private:  
        // Private constructor to prevent instantiation
        HeapMapper() {}
        // Private copy constructor and assignment operator to prevent copying
        HeapMapper(const HeapMapper&) = delete;
        HeapMapper& operator=(const HeapMapper&) = delete;

        std::map<Object**, LinkedListNode<Object**>*> m_address_LLN ;

       
    public:
    static HeapMapper& getInstance() {
        static HeapMapper instance;
        return instance;
    }
    void deleteRefTree(Object** current) override ;

    void add_ptr_value(Object **ptr, Object* value) override;
    private:   
    void  updateReferenceTree(Object **ptr);
    void recDeleteRefTree(LinkedListNode<Object**>* current);

};

#endif // !__HEAP_MAPPER__H_

