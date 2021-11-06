#include <iostream>
#include <memory>
#include <ctime>


#include "TEST.h"

template <typename T>
class stack
{
public:
    stack():count(0), bucket_size(2), bucket_index(0)
    {
        storage[bucket_index] = new T[bucket_size];
    };
    ~stack()
    {
        for (int i=0; i<=bucket_index; ++i)
            delete storage[i];
    };

    void push(T val)
    {
        if (count==bucket_size)
        {
            if (bucket_size>=INT_MAX/2)
                throw std::runtime_error("stack overflow!");
            bucket_size*=2;
            storage[++bucket_index] = new T[bucket_size];
            count=0;
        };
        storage[bucket_index][count++]=val;
    };
    T pop()
    {
        if (bucket_index==0 && count==0)
            throw std::runtime_error("stack exausted!");
        if (count==0)
        {
            delete[] storage[bucket_index--];
            bucket_size/=2;
            count = bucket_size;
        };
        return storage[bucket_index][--count];
    };
    void printContent()
    {
        int stack_size = count;
        for (int i=0; i<bucket_index; ++i)
        {
            stack_size+=(1<<(i+1));
        }
        std::cout<<"stack content ("<<stack_size<<" elements):"<<std::endl;
        for (int j=count-1; j>=0; --j)
            std::cout<<storage[bucket_index][j]<<std::endl;
        int current_size = bucket_size/2;
        for (int i=bucket_index-1; i>=0; --i)
        {
            for (int j=current_size-1; j>=0; --j)
                std::cout<<storage[i][j]<<std::endl;
            current_size/=2;
        }
        std::cout<<std::endl;
    }

private:

    int count;
    T* storage[sizeof(int)*8-2];
    int bucket_size;
    int bucket_index;

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
    newStack2.push(5.3234);
    newStack2.push(6);
    newStack2.push(7);
    std::cout<<std::endl<<std::endl;
    newStack2.printContent();



    return 0;
}




