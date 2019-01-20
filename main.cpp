#include "FiboHeap.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    FiboHeap fiboHeap;
    fiboHeap.push(5);
    fiboHeap.push(3);
    fiboHeap.push(2);
    fiboHeap.push(4);
    fiboHeap.push(0);
    fiboHeap.decrease_value(5, -2);
    fiboHeap.show_roots();
    std::cout << "\nNumber of nodes: " << fiboHeap.size() << "\nMinRoot: " << fiboHeap.top();
    return 0;
}