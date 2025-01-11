#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <cstddef>
#include "heap_mapper.hpp"
class Object{
private:
    bool mark_bit ;
    const int integrity = 123456789 ;
    friend class GC ;
    friend class HeapMapper ;
    friend void allocateAndRegister(Object** ptr);


public:
    int y;
    Object() :mark_bit{false} {};
    ~Object() ;
};
#endif // !__OBJECT_H__


