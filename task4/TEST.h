#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>
#include <assert.h>
#include <stdexcept>

#define TEST(_TestName, _Expression, _Value) \
    std::cout<<_TestName; \
    if ((_Expression)==(_Value)) std::cout<<" - passed"<<std::endl; \
    else \
    { \
        std::cout<<" - failed"<<std::endl; \
        std::cout<<"Condition: "<<#_Expression<<", got: "<<_Expression<<", expected: "<<#_Value<<", file: "<<__FILE__<<", line: "<<__LINE__<<std::endl; \
    }\

#define TEST_PROC(_TestName, _Expression) \
    std::cout<<_TestName; \
    try\
    {\
    _Expression;\
    std::cout<<" - passed"<<std::endl; \
    }\
    catch (std::exception& e)\
    { \
        std::cout<<" - failed"<<std::endl; \
        std::cout<<"call: "<<#_Expression<<" exception, file: "<<__FILE__<<", line: "<<__LINE__<<std::endl<<", what(): "<<e.what(); \
    }\


#endif // TEST_H_INCLUDED
