#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <cstddef>
#include "heap_mapper.hpp"
class Object{
private:
    bool mark_bit ;
    unsigned long long sizeofclass = 0 ;
    friend class GC ;
    friend class HeapMapper ;
    friend void allocateAndRegister(Object** ptr);
    template <typename T, typename... Args> friend void neo(T** ptr,  Args&&... args);
    template <typename T> friend void neo(T** ptr);


public:
    int y;
    Object() :mark_bit{false} {};
    ~Object() ;
};
#endif // !__OBJECT_H__


