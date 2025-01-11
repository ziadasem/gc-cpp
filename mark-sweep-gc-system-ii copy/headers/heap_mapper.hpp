#ifndef __HEAP_MAPPER__H_

#define __HEAP_MAPPER__H_

#include "heap_interface.hpp"


class HeapMapper : public HeapInterface {
    private:  
        // Private constructor to prevent instantiation
        HeapMapper() {}
        // Private copy constructor and assignment operator to prevent copying
        HeapMapper(const HeapMapper&) = delete;
        HeapMapper& operator=(const HeapMapper&) = delete;
        void addObject(Object* value) override;
        void addPtr(Object*& value);
    public:
    // Public methods
    // Static method to get the single instance of HeapMapper
    static HeapMapper& getInstance() {
        static HeapMapper instance;  // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    // Public methods for manipulating the unordered_map and unordered_set
    void add_ptr_value(Object **ptr, Object* value) override;

    private:   
};

#endif // !__HEAP_MAPPER__H_

