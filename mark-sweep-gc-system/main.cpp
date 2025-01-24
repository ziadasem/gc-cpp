#include <windows.h>
#include "headers/neo-all-inc.hpp"

#define TEST_CASE_1 1 //pass 
#define TEST_CASE_2 1 //pass
#define TEST_CASE_3 1 //pass
#define TEST_CASE_4 1 //pass
#define TEST_CASE_5 1 //pass
#define TEST_CASE_6 1 //pass
#define TEST_CASE_7 1 //pass 

#define TEST_CASE_8 1 //pass
#define TEST_CASE_9 1 //pass
#define TEST_CASE_10 0 //fail

int failedTestCases = 0;

class A : public Object {
    public:
        A* next ;
        A* next_2 ;
        A* next_3 ;
        A* next_4 ;
        A* next_5 ;
        A(){}
        A(int x)  { Object::y = x ;}
};


class B : public Object {
    public:
        B* next1 ;
        B* next2 ;
};

class C : public B {
    public:
        C* next1c ;
};
template<typename T> 
void runTestCase (std::string testName, T actualValue, T expectedValue){
    bool condition = (actualValue == expectedValue);
    std::string failedTestCaseReport;
    if (!condition) {
        failedTestCases ++ ;
        failedTestCaseReport = "expected: " + std::to_string(expectedValue) + " and found: " + std::to_string(actualValue)   ;
    }
    std::cout << (condition? "\033[32m": "\033[31m") << testName << ": " << (condition? "PASS " : "FAIL ") << failedTestCaseReport  <<"\033[0m" << std::endl;
    
}

void enableANSIColors() { //enable ANSI Colors for windows
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hConsole, &dwMode)) {
            SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
}


A* globalPtr = nullptr;

void foo(){
    A* localToStack = nullptr;
    neo(&localToStack);
}
void foo2(){
    int x = 100 ;
    int y = 100 ;
    int z = 100 ;
    int w[100];
}

int main(){
    enableANSIColors();
    GC& gc = GC::getInstance(HeapMapper::getInstance());
    // 1- Testing multiple roots with multiple children references in same calling stack
    // 1.1 no objects to be cleaned up
    #if TEST_CASE_1
    {
       A* root1 = nullptr;
       A* root2 = nullptr;

       neo(&root1);
       neo(&root1->next); 
       neo(&root1->next_3);
       neo(&root1->next->next_2); 
        neo(&root1->next->next_2->next_5); 
       
       neo(&root2);
            neo(&root2->next_2);
            neo(&root2->next_5);
                 neo(&root2->next_2->next_4);
        neo(&root1->next->next_5);

        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.1 no objects to be cleaned up ", cleanObjects,0); 
        root1 = nullptr;
        root2 = nullptr;
    }
    #endif

    //1.2 remove nodes from the reference tree
    #if TEST_CASE_2
    {
       A* root1 = nullptr;
       A* root2 = nullptr;

       neo(&root1); //0xe81b1ff618 -> 0x24dbad66050
       neo(&root1->next);  //0x24dbad66068 -> 0x24dbad665f0
       neo(&root1->next_3); // 0x24dbad66078  -> 0x24dbad660f0  (del)
       
       neo(&root1->next->next_2); //0x24dbad66610        0x24dbad65c40
        neo(&root1->next->next_2->next_5);  // 0x24dbad65c78        0x24dbad66820
    
       neo(&root1->next_3->next_5); // 0x24dbad66128        0x24dbad663c0  (del)       

       root1->next_3 = nullptr; //delete 2
       
       neo(&root2); //create 0xe81b1ff610
            neo(&root2->next_2);
            neo(&root2->next_5);
                 neo(&root2->next_2->next_4);
        neo(&root1->next->next_5);

        root2->next_2 = nullptr ; //delete 2
        
        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.2 remove nodes from the reference tree ", cleanObjects , 
        #if TEST_CASE_1 
            14
        #else
            4
        #endif
        ); 
    }
    #endif
   
    //1.3 remove objects that there pointers points to other objects
    #if TEST_CASE_3
    {
       A* root1 = nullptr;
       A* root2 = nullptr;

       neo(&root1);
       neo(&root1->next); 
       neo(&root1->next_3);// 5108 -> 9a0
       
       neo(&root1->next->next_2);  
        neo(&root1->next->next_2->next_5); 
    
       neo(&root1->next_3->next_5); 

       root1->next_3 = nullptr; //delete 2
       
       neo(&root2);
            neo(&root2->next_2);
            neo(&root2->next_5);
                 neo(&root2->next_2->next_4);
        neo(&root1->next->next_5);
        
        int cleanedObjects = gc.garbageCollect();
        runTestCase<int>("1.3 remove objects that there pointers points to other objects ", cleanedObjects , 2); 
    }
    #endif

    //1.4 remove one root
    #if TEST_CASE_4
    {
       A* root1 = nullptr;
       A* root2 = nullptr;

       neo(&root1);
       neo(&root1->next); 
       neo(&root1->next_3);
       
       neo(&root1->next->next_2); 
        neo(&root1->next->next_2->next_5); 
    
       neo(&root1->next_3->next_5);

       
       neo(&root2);
            neo(&root2->next_2);
            neo(&root2->next_5);
                 neo(&root2->next_2->next_4);
        neo(&root1->next->next_5);

        root1 = nullptr; //delete 7
        
        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.4 remove one root ", cleanObjects , 7); 
    }
    #endif

    //1.5 remove one root and two leafs
    #if TEST_CASE_5
    {
       A* root1 = nullptr;
       A* root2 = nullptr;

       neo(&root1);
       neo(&root1->next); 
       neo(&root1->next_3);
       
       neo(&root1->next->next_2); 
        neo(&root1->next->next_2->next_5); 
       
       root1 = nullptr; //5
    
       neo(&root1);
       neo(&root1->next_5);
       neo(&root1->next_5->next_5);
       root1->next_5->next_5 = nullptr ; //1

       
       neo(&root2);
            neo(&root2->next_2);
            neo(&root2->next_5);
                 neo(&root2->next_2->next_4);
       
        root2->next_2->next_4 = nullptr; //delete leef
        
        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.5 remove one root ", cleanObjects , 7); 
    }
    #endif

    //1.6 remove one object with children and its children has children and brothers, and the node itself has children has brothers
    #if  TEST_CASE_6
    { 
        A* root1 = nullptr;
        neo(&root1);
            neo(&root1->next);
            neo(&root1->next_2);
            neo(&root1->next_3); //to be deleted 0x24dbad66140 D
            neo(&root1->next_4); // has brothers
                neo(&root1->next_4->next); //should not be deleted 
                neo(&root1->next_4->next_3); //should not be deleted

                neo(&root1->next_3->next); // has a child 
                neo(&root1->next_3->next_2); // has another 
                neo(&root1->next_3->next_3); // has another child 
                    neo(&root1->next_3->next_2->next); //child has a child 
                    neo(&root1->next_3->next_2->next_2); //child has a brother 
                    neo(&root1->next_3->next_2->next_3); //child has a brother
                        neo(&root1->next_3->next_2->next->next_5); //child has a brother has a child 
             neo(&root1->next->next_5); //should not be deleted
        root1->next_3 = nullptr ;
        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.6 remove one object with children and its children has children and brothers, and the node itself has children has brothers ", cleanObjects , 8); 
    }
    #endif 

    //1.7 replace a pointer with a new object
    #if TEST_CASE_7
    {
       A* root1 = nullptr;
       neo(&root1);
       neo(&root1->next_3);

       neo(&root1->next); 
       neo(&root1->next->next_3);
       neo(&root1->next->next_5);
       neo(&root1->next->next_5->next);
       neo(&root1->next->next_5->next_2);
       neo(&root1->next->next_5->next_3);
       neo(&root1->next->next_5->next_2->next_5);
       neo(&root1->next->next_3->next_5);

       neo(&root1->next_4);
       neo(&root1->next_4->next);

       neo(&root1->next); 
       neo(&root1->next->next_3);
       neo(&root1->next->next_5);
       neo(&root1->next->next_4);
       neo(&root1->next->next_4->next_2);
       neo(&root1->next_3->next_2);
           
        int cleanObjects = gc.garbageCollect();
        runTestCase<int>("1.7 replace a pointer with a new object ", cleanObjects , 8); 
    }
    #endif

    // 2- Testing global and stack reference
    A* globalToScope = nullptr;
    
    //2.1- Testing global pointer
    #if TEST_CASE_8
    {
        neo(&globalPtr);
    }
    {
         neo(&globalPtr);
         int cleanObjects = gc.garbageCollect();
         runTestCase<int>("2.1- Testing global pointer ", cleanObjects , 1); 
    }
    #endif

    //2.2 test stack reference after replacing the stack frame
    #if TEST_CASE_9
    {
        foo();
        foo2();
    }
    {
          foo();
          foo2();
          foo();
          foo2();
         int cleanObjects = gc.garbageCollect();
         runTestCase<int>("2.2- Test stack reference after replacing the stack frame", cleanObjects , 3); 
    }
    #endif


    //2.3 test stack reference before replacing stack frame --fail
    #if TEST_CASE_10
    {
       foo();
    }
    {
         foo();
         int cleanObjects = gc.garbageCollect();
         runTestCase<int>("2.3- Test stack reference without replacing the stack frame ", cleanObjects , 2); 
    }
    #endif
    runTestCase<int>("All test cases are success ", failedTestCases , 0); 
    return 0;
}

