#ifndef __HEAP_MAPPER__H_

#define __HEAP_MAPPER__H_

#include "heap_interface.hpp"
#include <unordered_set>
#include <unordered_map>

class HeapMapper : public HeapInterface {
    private:  
        // Private constructor to prevent instantiation
        HeapMapper() {}
        // Private copy constructor and assignment operator to prevent copying
        HeapMapper(const HeapMapper&) = delete;
        HeapMapper& operator=(const HeapMapper&) = delete;

        std::unordered_map<void*, void*> m_rootvariables_variable_value ;
        std::unordered_set<void*> m_objects ;

    public:
    // Public methods
    // Static method to get the single instance of HeapMapper
    static HeapMapper& getInstance() {
        static HeapMapper instance;  // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    // Public methods for manipulating the unordered_map and unordered_set
    void addRootObject(void* key, void* value) override;
    void addObject(void* value) override;

    void removeRootVaraible(void* key) override;
    bool containsObject(void* key) override;

    private:   
};

#endif // !__HEAP_MAPPER__H_

