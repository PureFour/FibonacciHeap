#include "FiboHeap.h"

FiboHeap::FiboHeap()
{
    this->min_root = nullptr;
    this->n = 0;
    //...
}

void FiboHeap::push(int x)
{
    //creates new singleton tree and add it to roots[]
    //update min_root if necessary

    Node* singleton = new Node;
    singleton->value = x;
    singleton->left = singleton->right = singleton;
    singleton->parent = singleton->child = nullptr;
    singleton->rank = 0;
    singleton->marked = false;
    singleton->F = 'N';

    if(this->min_root == nullptr) //heap is empty
    {
        this->min_root = singleton;
    }
    else this->min_root = link(this->min_root, singleton);
    this->n++;
}

int FiboHeap::pop()
{
    return 0;
}

int &FiboHeap::top()
{
    return this->min_root->value;
}

int FiboHeap::size()
{
    return this->n;
}

void FiboHeap::decrease_value(int key, int value) //decreasing n-value to value
{
    if(this->min_root == nullptr)
    {
        std::cout << "Heap is empty!\n";
        return;
    }
    Node* n = find(this->min_root, key);
    if(n == nullptr)
    {
        std::cout << "Node doesn't exist!\n";
        return;
    }
    n->value = value; //changing it's value
    Node* n_parent = n->parent;
    if(n_parent && n->value < n_parent->value) //when parent has higher value we need to cut children
    {
        cut_child(n, n_parent);
        cut_recursively(n_parent);
    }
    if(n->value < this->min_root->value) //update min_root if necessary
    {
        this->min_root = n;
    }
}

void FiboHeap::remove(int)
{

}

void FiboHeap::show_roots()
{
    if(this->min_root == nullptr)
    {
        std::cout << "Heap is empty!\n";
        return;
    }
    Node* ptr = this->min_root;
    std::cout << "Roots: ";
    do
    {
        std::cout << ptr->value << "[" << ptr->rank << "] ";
        ptr = ptr->right;

    } while(ptr != this->min_root); //loop through all nodes...
}

FiboHeap::Node* FiboHeap::link(FiboHeap::Node *n1, FiboHeap::Node *n2)
{
    if(n1 == nullptr) return n2;
    if(n2 == nullptr) return n1;
    if(n1->value > n2->value) //swapping n1|n2 when n2 is bigger
    {
        Node* temp = n1;
        n1 = n2;
        n2 = temp;
    }
    Node* n1_right = n1->right;
    Node* n2_left = n2->left;
    n1->right = n2;
    n2->left = n1;
    n1_right->left = n2_left;
    n2_left->right = n1_right;
    return n1;
}

void FiboHeap::un_link(FiboHeap::Node* n)
{
    if(n->right == n) //when its only one
        return;
    Node* n_right = n->right;
    Node* n_left = n->left;
    n_left->right = n_right;
    n_right->left = n_left;
}

void FiboHeap::cut_child(FiboHeap::Node* child, FiboHeap::Node* parent)
{
    un_link(child);
    if(child->right == child) //when its only one
        parent->child = nullptr;
    else
        parent->child = child->right; //setting parent's a new child (old child's sibling)
    parent->rank--;
    link(this->min_root, child); //linking child to the roots_list (making a new root)
    child->parent = nullptr;
    child->marked = false;
}

void FiboHeap::cut_recursively(FiboHeap::Node * n)
{
    Node* n_parent = n->parent;
    while(n_parent)
    {
        if(n_parent->marked == false) n_parent->marked = true; //we marks parent because he lost child
        else //we need to cut childer when parent has already lost one
        {
            cut_child(n, n_parent);
            cut_recursively(n_parent);
        }
    }
}

FiboHeap::Node *FiboHeap::find(FiboHeap::Node * n, int x) //function finds node by given x-value
{
    Node* found = nullptr;
    Node* tmp = n;
    tmp->F = 'Y';
    if(tmp->value == x)
    {
        found = tmp;
        tmp->F = 'N';
        return found;
    }
    //if(found == nullptr)
    {
        if(tmp->child != nullptr) found = find(tmp->child, x);
        if(tmp->right->F != 'Y') found = find(tmp->right, x);
    }
    tmp->F = 'N';
    return found;
}



