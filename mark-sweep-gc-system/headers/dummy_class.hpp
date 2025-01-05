#ifndef __DUMMY_CLASS__H_
#define __DUMMY_CLASS__H_

#include "object.hpp"

class DummyClass : public Object {
    public:
        DummyClass* next ;
        int id;
        DummyClass(int id): id{id} {}
};

#endif // !__DUMMY_CLASS__H_