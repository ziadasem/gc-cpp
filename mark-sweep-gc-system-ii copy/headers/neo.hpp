#ifndef __neo_h__
#define __neo_h__

#include <type_traits>
#include <utility>
#include "object.hpp"
#include "heap_mapper.hpp"

#include <iostream>

class Object;
class HeapMapper;

#include <utility>

void allocateAndRegister(Object** ptr) {
     HeapMapper::getInstance().add_ptr_value(ptr, *ptr); // Create new root
}

template <typename T, typename... Args>
void neo(T** ptr,  Args&&... args) { 
    *ptr = new T(std::forward<Args>(args)...); // Points to new heap object
    allocateAndRegister((Object **) ptr);
}

template <typename T>
void neo(T** root) {
    *root = new T(); // Default constructor
    allocateAndRegister((Object **) root);
}




#endif // !__neo_h__
