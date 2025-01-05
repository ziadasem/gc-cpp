#include "headers/dummy_class.hpp"
#include "headers/garbage_collector.hpp"
#include "headers/heap_mapper.hpp"
#include <iostream>
#define print(X) {std::cout << X <<std::endl;}
int main(){
    HeapMapper mapper;
    GC gc(mapper);

    DummyClass* dummy1 = new DummyClass(1) ;
    mapper.add_root(dummy1);
    dummy1->next = new DummyClass(2) ;
    dummy1->add_reference(dummy1->next);
    mapper.add(dummy1);
    dummy1->next->next = new DummyClass(3);
    //dummy1->next->add_reference(dummy1->next->next);
    mapper.add(dummy1->next->next);

    print("Freed Count: " << gc.garbageCollect() );
    print(dummy1->next->next->id);

}