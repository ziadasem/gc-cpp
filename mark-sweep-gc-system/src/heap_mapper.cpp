#include "../headers/heap_mapper.hpp"

void HeapMapper::add(Object* obj) {
    m_object_address.insert(obj);
}
void HeapMapper::remove(Object* obj) {     
    m_object_address.erase(
        std::find(m_object_address.begin(), m_object_address.end(), obj)
    );    
}
void HeapMapper::add_root(Object* obj) {
    m_root_set.insert(obj);
    this->add(obj);
}
void* HeapMapper::get_root_set()
{
    return static_cast< std::unordered_set<Object*>*>(&m_root_set);
}
void* HeapMapper::get_object_address()
{
    return static_cast< std::unordered_set<Object*>*>(&m_object_address);
}