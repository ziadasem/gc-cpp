#ifndef __PRNT
#define __PRNT
#include <iostream>


#if __DEBUG__  //set by CMake
    #define print(X) {std::cout << X << std::endl;}
#else
    #define print(X) {}
#endif
#endif // !__PRNT

