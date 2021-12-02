#include <iostream>

#include "TEST.h"
#include "stack.h"

struct Block{
    int size;
    friend std::ostream& operator<< (std::ostream& stream, const Block& block)
    {
        stream << "Block <" << block.size << ">";
        return stream;
    }
};

typedef LearnCPP::stack<Block> CTower;

void MakeMove(LearnCPP::stack<Block> towers[], int from, int to)
{
    auto movedBlock = towers[from].pop();
    towers[to].push(movedBlock);
    std::cout << "Move " << movedBlock << " from tower " << from << " to tower " << to << std::endl;
}

void MoveTower(LearnCPP::stack<Block> towers[], int count, int from, int to)
{
    assert(from!=to);
    assert(from<=2);
    assert(to<=2);
    assert(!towers[from].isEmpty());
    assert(count>=1);

    int temp = 3 - from - to;
    if (count>1)
    {
        MoveTower(towers, count-1, from, temp);
        MakeMove(towers, from, to);
        MoveTower(towers, count-1, temp, to);
    }
    else
    {
        MakeMove(towers, from, to);
    }
}


int main()
{
    const int BlocksCount = 8;
    std::cout << "Tower of Hanoi tests:" << std::endl;

    LearnCPP::stack<Block> Towers[3];
    for (int i=BlocksCount; i>=1; i--)
    {
        Towers[0].push(Block{i});
    }
    for (int i=0;i<3;i++)
    {
        std::cout << "Tower " << i << " content:" << std::endl;
        Towers[i].printContent();
    }

    MoveTower(Towers,BlocksCount,0,2);

    for (int i=0;i<3;i++)
    {
        std::cout << "Tower " << i << " content:" << std::endl;
        Towers[i].printContent();
    }

    TEST("Source tower is empty", Towers[0].isEmpty(), true);
    TEST("Destination tower is not empty", Towers[2].isEmpty(), false);
}

