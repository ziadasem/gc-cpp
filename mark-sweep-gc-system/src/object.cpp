#include "../headers/object.hpp"
#include <iostream>

void Object::add_reference(Object* obj) { m_references.push_back(obj); }
void Object::remove_reference(Object* obj) 
{ 
    m_references.erase(
        std::find(m_references.begin(), m_references.end(), obj)
    ); 
}
