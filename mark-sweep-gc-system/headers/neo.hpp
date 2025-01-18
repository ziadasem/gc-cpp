#ifndef __neo_h__
#define __neo_h__

#include <type_traits>
#include <utility>
#include "object.hpp"
#include "heap_mapper.hpp"
#include "print.hpp"

class Object;
class HeapMapper;

#include <utility>

void allocateAndRegister(Object** ptr) {
     HeapMapper::getInstance().add_ptr_value(ptr, *ptr); // Create new root
}

template <typename T, typename... Args>
void neo(T** ptr,  Args&&... args) { 
    *ptr = new T(std::forward<Args>(args)...); // Points to new heap object
    reinterpret_cast<Object*>(*ptr)->sizeofclass = sizeof(T);
    allocateAndRegister((Object **) ptr);
}

template <typename T>
void neo(T** ptr) {
    *ptr = new T(); // Default constructor
    reinterpret_cast<Object*>(*ptr)->sizeofclass = sizeof(T);
    allocateAndRegister((Object **) ptr);
}




#endif // !__neo_h__
