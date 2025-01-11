#include "../headers/object.hpp"
#include <iostream>

void Object::ObjectCtor(void *instance)
{
    mark_bit = false;
    m_instance = instance;
    m_mapper = nullptr;    
}

Object::Object(): Object(nullptr)
{
}

Object::Object(void* instance)
{
    ObjectCtor(instance);
}

void Object::ObjectCtor() { ObjectCtor(nullptr); }



// void* operator new(size_t size) {
//     // Allocate memory for the object
//     void* ptr = malloc(size);
//     Object* o = (Object* ) malloc(sizeof(Object)) ;
//     o->ObjectCtor(ptr);
//     return o;
// }

