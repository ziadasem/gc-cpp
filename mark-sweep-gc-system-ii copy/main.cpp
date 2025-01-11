#include <iostream>
#define print(X) {std::cout << X << std::endl;}
#include "headers/object.hpp"
#include "headers/garbage_collector.hpp"
#include "headers/heap_mapper.hpp"
#include "headers/neo.hpp"

#include <chrono> // For std::chrono::seconds
#include <thread> // For std::this_thread::sleep_for



class A : public Object {
    public:
        int integrity = 123456789 ;
        A(){ a[0] = 10 ;}
        
        int a[10000];
        A* next ;
        A(int x)  { Object::y = x ; a[0] = 10 ;}
};


int main(){
    GC& gc = GC::getInstance(HeapMapper::getInstance());
    A* abc = nullptr;
    for (int i = 0; i < 10 ; i++) {
        neo<A>(&abc, i);
        neo<A>(&(abc->next));
    }

    
    //std::this_thread::sleep_for(std::chrono::seconds(4));

    int cleanObjects = gc.garbageCollect();
    print("Number of cleaned objects: " <<cleanObjects);
    
    return 0;
}