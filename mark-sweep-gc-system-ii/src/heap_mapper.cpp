#include "../headers/heap_mapper.hpp"

void HeapMapper::addRootObject(void* value, void* root_variable) {
    m_rootvariables_variable_value[root_variable] = value;
    m_objects.insert(value);
    m_objects.insert(value);
}

void HeapMapper::addObject(void *value)
{
    m_objects.insert(value);
}

void HeapMapper::removeRootVaraible(void* key) {
    m_rootvariables_variable_value[key] = nullptr;
}

bool  HeapMapper::containsObject(void* key) {
    return m_objects.find(key) != m_objects.end();
}


