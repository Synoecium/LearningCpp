#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

namespace LearnCPP {

/// mixed way of storage - list+arrays
template <typename T>
class stack
{
    const int MAX_CHUNK_SIZE = 1<<23;   //32 Mb for 4 bytes elements
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
        if (isEmpty())
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
        int64_t stack_size = count;
        if (!isEmpty())
        {
            auto prev_chunk = curr_chunk->prev_chunk;
            for (int j=count-1; j>=0; --j)
                std::cout << curr_chunk->bucket[j] << std::endl;
            prev_chunk = curr_chunk->prev_chunk;
            while (prev_chunk!=nullptr)
            {
                for (int j=prev_chunk->size-1; j>=0; --j)
                    std::cout << prev_chunk->bucket[j] << std::endl;
                stack_size+=prev_chunk->size;
                prev_chunk = prev_chunk->prev_chunk;
            }
        }
        std::cout << "-------------" << std::endl;
        std::cout << "stack content (" << stack_size << " elements)" << std::endl;
        std::cout << std::endl;
    }
    bool isEmpty() {return (curr_chunk==nullptr || (curr_chunk->prev_chunk==nullptr && count==0));};

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

}

#endif // STACK_H_INCLUDED
