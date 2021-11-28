#include <iostream>

#include "TEST.h"

void ShowMove(int number, int from, int to)
{
    std::cout<<"Move block "<<number<<" from tower "<<from<<" to tower "<<to<<std::endl;
}


void MoveTower(int count, int from, int to)
{
    int temp = 3 - from - to;
    if (count>1)
    {
        MoveTower(count-1, from, temp);
        ShowMove(count, from, to);
        MoveTower(count-1, temp, to);
    }
    else
    {
        ShowMove(count, from, to);
    }
}


int main()
{
    std::cout << "Tower of Hanoi tests:" << std::endl;
    MoveTower(8,0,2);
}
