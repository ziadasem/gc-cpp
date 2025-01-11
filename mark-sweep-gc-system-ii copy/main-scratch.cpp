#include <iostream>
#include "headers/object.hpp"
#include "headers/garbage_collector.hpp"
#include "headers/heap_mapper.hpp"
#include "headers/neo.hpp"


#define print(X) {std::cout<< X <<std::endl;}

#include <csignal>
#include <cstdlib>

// Signal handler function
void handleSegmentationFault(int signal) {
    std::cerr << "Segmentation fault (signal " << signal << ") caught!" << std::endl;
    // Optionally, exit the program gracefully
   // std::exit(signal);
}

template <typename T>
class PointerWrapper {
private:
    T* ptr;

public:
    // Constructor
    PointerWrapper(T* p = nullptr) : ptr(p) {}

    // Copy assignment operator
    PointerWrapper& operator=(T* newPtr) {

        
        if (ptr != newPtr) {
            delete ptr; // Clean up old memory
            ptr = newPtr; // Assign new pointer
        }
        return *this;
    }

    // Dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

    // Destructor
    ~PointerWrapper() {
        //TODO
        //delete ptr;
    }
};



class A : public Object {
    public:
        int integrity = 123456789 ;
        A(){ a[0] = 10 ; y = 5 ; print("A::A() empty");}
        int y;
        int a[10000];
        PointerWrapper<A> next ;
        A(int x) : y(x) { a[0] = 10 ; print("A::A()"); }
};


int main(){
    GC& gc = GC::getInstance(HeapMapper::getInstance());
    
    return 0;
}