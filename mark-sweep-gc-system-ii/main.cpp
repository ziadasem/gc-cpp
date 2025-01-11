#include "headers/object.hpp"
#include <iostream>
#define print(X) {std::cout << X <<std::endl;}
#include <unordered_map>
#include <unordered_set>
class ObjVar;

std::unordered_map<void*, void*> roots;
std::unordered_set<ObjVar*> objects;


class ObjVar {
    private:
       ObjVar(){x = 11; instance = nullptr;}
    public:
        
        int x = 10 ;
        ObjVar* instance ;
        ObjVar* next ;
        ObjVar(ObjVar* x) {
            instance = x ;
            roots.insert(this, instance);
            
        }
    
    ObjVar& operator=(ObjVar* objVarPtr) {
        instance = objVarPtr;
        roots.insert(this, instance);
        objects.insert(objVarPtr);
        return *this; // Return *this to allow chaining
    }

    void* operator new(size_t size) {
        //put your self in heap mappers (referenced object)
        ObjVar* ptr = (ObjVar*) ::new(std::nothrow) ObjVar();
        objects.insert(ptr);
        return ptr;
    }
};

int main(){
   Object obj ;
   obj = new A();
   ((A*) obj->)a ;
   print( ) ;
}