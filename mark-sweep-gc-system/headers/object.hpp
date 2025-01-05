#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <algorithm>
class Object {
    private:
        
        bool mark_bit ;
        std::vector<Object*> m_references ;
        friend class GC ;
    public:
        
        Object() : mark_bit{false} {}
        void add_reference(Object* obj);
        void remove_reference(Object* obj);

};

#endif // !__OBJECT_H__

