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
        A* next ;
        A* next_2 ;
        A* next_3 ;
        A* next_4 ;
        A* next_5 ;

        int integrity = 123456789 ;
        A(){}
        
       
        A(int x)  { Object::y = x ;}
};

class P {
    public:
        int x = 10;
};
class C  : public P{
    public:
        int y = 10;
        int z = 10;
};

void stackRef(){
     A* abc = nullptr;
     for (int i = 0; i < 5 ; i++) {
        neo<A>(&abc, i);
        neo<A>(&(abc->next), i * 10);
    }
}


int main(){

    GC& gc = GC::getInstance(HeapMapper::getInstance());
    A* abc = nullptr;
    neo<A>(&abc);
    neo<A>(&(abc->next));
    neo<A>(&(abc->next->next));
    neo<A>(&(abc->next->next_2));

    neo<A>(&(abc->next->next_4));
        neo<A>(&(abc->next->next_4->next));
        neo<A>(&(abc->next->next_4->next_3));
            neo<A>(&(abc->next->next_4->next_3->next_2));

    neo<A>(&(abc->next->next_5));
        neo<A>(&(abc->next->next_5->next_2));
        
    neo<A>(&(abc->next->next_3));
    neo<A>(&(abc->next->next_3->next_2));

    abc->next->next_4 = nullptr;
    abc->next->next_5 = nullptr;
    //std::this_thread::sleep_for(std::chrono::seconds(4));

    int cleanObjects = gc.garbageCollect();
    print("Number of cleaned objects: " <<cleanObjects);
    
    return 0;
}