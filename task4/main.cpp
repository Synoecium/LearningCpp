#include <iostream>
#include <memory>
#include <ctime>


#include "TEST.h"

/*
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
*/

//mixed way of storage - list+arrays
template <typename T>
class stack
{
    const int MAX_CHUNK_SIZE = 1<<23;   //8 Mb
public:
    stack() : count(0)
    {

    };
    ~stack()
    {
        if (curr_chunk==nullptr)
        {
            return;
        }
        auto prev_chunk = curr_chunk->prev_chunk;
        delete[] curr_chunk->bucket;
        delete curr_chunk;
        while (prev_chunk!=nullptr)
        {
            delete[] prev_chunk->bucket;
            auto temp_ptr = prev_chunk->prev_chunk;
            delete prev_chunk;
            prev_chunk = temp_ptr;
        }
    };

    void push(T val)
    {
        if (curr_chunk==nullptr || count==curr_chunk->size)
        {
            auto prev_chunk = curr_chunk;
            curr_chunk = new TChunk;
            if (prev_chunk==nullptr)
            {
                curr_chunk->size = 2;
            }
            else
            {
                curr_chunk->size = (prev_chunk->size*2 > MAX_CHUNK_SIZE ? MAX_CHUNK_SIZE : prev_chunk->size*2);
            }
            curr_chunk->bucket = new T[curr_chunk->size];
            curr_chunk->prev_chunk = prev_chunk;
            count = 0;
        }
        curr_chunk->bucket[count++]=val;

    };
    T pop()
    {
        if (curr_chunk==nullptr || (curr_chunk->prev_chunk==nullptr && count==0))
            throw std::runtime_error("stack exausted!");
        if (count==0)
        {
            auto prev_chunk = curr_chunk->prev_chunk;
            delete[] curr_chunk->bucket;
            delete curr_chunk;
            curr_chunk = prev_chunk;
            count = curr_chunk->size;
        }
        return curr_chunk->bucket[--count];
    };
    void printContent()
    {
        int stack_size = count;
        auto prev_chunk = curr_chunk->prev_chunk;
        while (prev_chunk!=nullptr)
        {
            stack_size+=prev_chunk->size;
            prev_chunk = prev_chunk->prev_chunk;
        }
        std::cout<<"stack content ("<<stack_size<<" elements):"<<std::endl;
        for (int j=count-1; j>=0; --j)
            std::cout<<curr_chunk->bucket[j]<<std::endl;
        prev_chunk = curr_chunk->prev_chunk;
        while (prev_chunk!=nullptr)
        {
            for (int j=prev_chunk->size-1; j>=0; --j)
                std::cout<<prev_chunk->bucket[j]<<std::endl;
            prev_chunk = prev_chunk->prev_chunk;
        }
        std::cout<<std::endl;
    }

private:

    struct TChunk
    {
        T* bucket;
        int size;
        TChunk* prev_chunk = nullptr;
    };
    TChunk* curr_chunk = nullptr;
    int count;

};


int main()
{
    std::cout<<"stack class tests:"<<std::endl;
    stack<int> newStack;
    TEST_PROC("test push", newStack.push(1));
    TEST("test pop", newStack.pop(), 1);
    //TEST_PROC("test pop with empty stack", newStack.pop());

    srand(static_cast<unsigned int>(time(0)));
    int testCount = std::rand()%1000+10000;
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




