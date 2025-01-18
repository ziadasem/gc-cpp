#ifndef __PRNT
#define __PRNT
#include <iostream>
#define __DEBUG__ 0  

#if __DEBUG__ == 1
    #define print(X) { std::cout << X << std::endl;}
#else
    #define print(X) {}
#endif
#endif // !__PRNT

