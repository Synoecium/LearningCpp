#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>
#include <assert.h>

#define TEST(_TestName, _Expression, _Value) \
    std::cout<<_TestName; \
    if ((_Expression)==(_Value)) std::cout<<" - passed"<<std::endl; \
    else \
    { \
        std::cout<<" - failed"<<std::endl; \
        std::cout<<"Condition: "<<#_Expression<<", got: "<<_Expression<<", expected: "<<#_Value<<", file: "<<__FILE__<<", line: "<<__LINE__<<std::endl; \
    }\


#endif // TEST_H_INCLUDED
