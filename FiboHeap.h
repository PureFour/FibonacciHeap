#ifndef FIBONACCIHEAP_FIBOHEAP_H
#define FIBONACCIHEAP_FIBOHEAP_H

#include <iostream>

class FiboHeap
{
    struct Node
    {
        int value;
        int rank;       //degree of node
        bool marked;    //node is marked when it has lost a child
        char V;         //flag for find function 'N' not visited 'Y' visited
        Node* left;     //left sibling
        Node* right;    //right sibling
        Node* parent;   //parent node
        Node* child;    //children nodes
    };
    Node* min_root;     //minimum value node (first level of heap contains circular linked list)
    int n;              //number of nodes

    Node* link(Node*, Node*); //function links nodes and returns smaller...
    void swapNodes(Node*, Node*); //function swaps nodes first becomes node with smaller value
    void un_link(Node*); //function unlinks given node from circular list...
    void cut_child(Node*, Node*); //function removes child from parent and adds to the roots_list
    void cut_recursively(Node*); //doing cut but recursively
    Node* find(Node*, int);
public:
    void consolidate();
    FiboHeap();
    void create_test();
    void push(int);
    void pop();
    int& top();
    int size();
    void decrease_value(int, int);
    void remove(int);

    void show_roots();
};
#endif //FIBONACCIHEAP_FIBOHEAP_H
