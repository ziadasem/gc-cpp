#ifndef __HEAP_INTERFACE__
#define __HEAP_INTERFACE__
#include "object.hpp"

class HeapInterfaces {
    private:
    public:
        virtual void add(Object* obj) =  0 ;
        virtual void remove(Object* obj) = 0;
        virtual void add_root(Object* obj) =0 ;

        virtual void * get_root_set()  =0 ;
        virtual void * get_object_address() =0 ;
};
#endif