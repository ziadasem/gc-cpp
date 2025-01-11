#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <cstddef>
#include <vector>

#include <iostream>

class Object{
private:
    void* m_instance;          // Pointer to the wrapped _Object
    const void* m_mapper;   // Hypothetical mapper (not used in this example)
    bool mark_bit ;
    std::vector<Object*> m_references ;
    friend class GC ;

public:
    // Constructor
    Object();
    Object(void* instance);
    void ObjectCtor(void* instance); 
    void ObjectCtor();
    // Destructor
    ~Object() {
        mark_bit = true; //Check this TODO
        //delete m_instance; // Free memory when the Object is destroyed
    }

    // Overloaded assignment operator
    void operator=(const Object& other) {
        //free linkage from mapper
        m_instance = other.m_instance;
        //link new instance in mapper
    }

    void operator=(std::nullptr_t) {
        m_instance = nullptr; // Free memory when
        //free from mapper
    }

    // Overloaded new operator to create an _Object and return its address
    void* operator new(size_t size, Object* that) {
        std::cout<<that->mark_bit<<std::endl;
        void* ptr = ::operator new(size); // Allocate memory for Object
        return ptr;
    }

    void* operator->() {
            return  m_instance;  // Returns the address of `value`
    }

    
};
#endif // !__OBJECT_H__


