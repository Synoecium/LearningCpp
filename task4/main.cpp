#include <iostream>
#include <memory>
#include <ctime>


#include "TEST.h"

template <typename T>
class stack
{
public:
    stack():count(0), stack_size(2)
    {
        head_ptr = new T[2];
    };
    ~stack(){ delete[] head_ptr;};

    void push(T val)
    {
        if (count>=stack_size)
        {
            stack_size*=2;
            T* new_head_ptr = new T[stack_size];
            for (int i=0; i<count; ++i)
            {
                new_head_ptr[i]=head_ptr[i];
            }
            delete head_ptr;
            head_ptr = new_head_ptr;
        }
        head_ptr[count++]=val;
    };
    T pop()
    {
        if (count==0)
            throw std::runtime_error("stack exausted!");
        return head_ptr[--count];
    };
    void printContent()
    {
        std::cout<<"stack content ("<<count<<" elements):"<<std::endl;
        for (int i=count-1; i>=0; i--)
            std::cout<<head_ptr[i]<<std::endl;
        std::cout<<std::endl;
    }

private:

    T* head_ptr;
    int count;
    int stack_size;

};




int main()
{
    std::cout<<"stack class tests:"<<std::endl;
    stack<int> newStack;
    TEST_PROC("test push", newStack.push(1));
    TEST("test pop", newStack.pop(), 1);
    //TEST_PROC("test pop with empty stack", newStack.pop());

    srand(static_cast<unsigned int>(time(0)));
    int testCount = std::rand()%100+10000;
    for (int i=0; i<testCount; ++i)
    {
        newStack.push(std::rand()%1000);
    }
    newStack.push(4);
    newStack.push(5);
    newStack.push(6);
    newStack.pop();
    newStack.pop();
    TEST("test pop with some values in stack", newStack.pop(), 4);

    /// visual test print content of stack
    stack<float> newStack2;
    newStack2.push(1.1);
    newStack2.push(2);
    newStack2.push(3);
    newStack2.push(4);
    std::cout<<std::endl<<std::endl;
    newStack2.printContent();



    return 0;
}




