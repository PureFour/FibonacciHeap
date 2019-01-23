#include "FiboHeap.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    FiboHeap fiboHeap;
    fiboHeap.push(1);
    fiboHeap.push(2);
    fiboHeap.push(3);
    fiboHeap.push(4);
    fiboHeap.push(5);
    fiboHeap.push(6);
    fiboHeap.push(7);
    fiboHeap.push(8);
    fiboHeap.push(9);
    fiboHeap.push(10);
    fiboHeap.show_roots();
    fiboHeap.pop();
//    fiboHeap.decrease_value(6, 0);
    fiboHeap.show_roots();
    std::cout << "\nNumber of nodes: " << fiboHeap.size() << "\nMinRoot: " << fiboHeap.top();
    return 0;
}