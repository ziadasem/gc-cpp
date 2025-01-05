#ifndef __HEAP_MAPPER_H__
#define __HEAP_MAPPER_H__

#include <unordered_set>
#include "heap_interface.hpp"

class HeapMapper : public HeapInterfaces {
    private:
        std::unordered_set<Object*> m_object_address ;
        std::unordered_set<Object*> m_root_set ;
    public:
        void add(Object* obj) override;
        void remove(Object* obj) override;
        void add_root(Object* obj) override;

        void* get_root_set() override ;
        void* get_object_address() override;
};

#endif // !__HEAP_MAPPER_H__