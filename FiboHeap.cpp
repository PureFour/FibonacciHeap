#include <cmath>
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
    singleton->V = 'N';

    if(this->min_root == nullptr) //heap is empty
    {
        this->min_root = singleton;
    }
    else this->min_root = link(this->min_root, singleton);
    this->n++;
}

void FiboHeap::pop() //  O(log(n))
{
    if(this->min_root != nullptr)
    {
        //first we need to unlink all children from min_root
        Node* temp = this->min_root->child;
        if(temp != nullptr)
        {
            do //  O(log(n))
            {
                temp->parent = nullptr;
                temp = temp->right;
            } while(temp != this->min_root->child);
        }
        un_link(this->min_root);
        link(this->min_root, this->min_root->child); //link children list to root_list
        if(this->min_root == this->min_root->right) //when it's only one node
        {
            this->min_root = nullptr;
        }
        else
        {
            //updating a min_root
            this->min_root = this->min_root->right;
//            Node* it = this->min_root = this->min_root->right; //setting a new minimum
//            do
//            {
//                if(it->value < this->min_root->value) this->min_root = it;
//                it = it->right;
//            } while(it != this->min_root);
            consolidate(); //  O(log(n))
        }
        this->n--; //decreasing number of nodes
    }
}

int &FiboHeap::top()
{
    return this->min_root->value;
}

int FiboHeap::size()
{
    return this->n;
}

void FiboHeap::decrease_value(int key, int value) //decreasing n-value to value O(1)
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

void FiboHeap::remove(int x) //O(log(n))
{
    if(this->min_root == nullptr) //when heap is empty
    {
        std::cout << "Heap is empty!\n";
        return;
    }
    if(this->min_root->right == this->min_root) //when its only one node
    {
        this->min_root = nullptr;
        this->n--;
        return;
    }
    decrease_value(x, -5000); //decreasing value
    pop(); //and removing this node
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

FiboHeap::Node* FiboHeap::link(FiboHeap::Node *n1, FiboHeap::Node *n2) //O(1)
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
    return n1; //returns smaller
}

void FiboHeap::un_link(FiboHeap::Node* n) //O(1)
{
    if(n->right == n) //when its only one
        return;
    Node* n_right = n->right;
    Node* n_left = n->left;
    n_left->right = n_right;
    n_right->left = n_left;
}

void FiboHeap::cut_child(FiboHeap::Node* child, FiboHeap::Node* parent) //O(1)
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

void FiboHeap::cut_recursively(FiboHeap::Node * n) //O(1)?
{
    Node* n_parent = n->parent;
    while(n_parent)
    {
        if(n->marked == false) n->marked = true; //we marks parent because he lost child
        else //we need to cut childer when parent has already lost one
        {
            cut_child(n, n_parent);
            cut_recursively(n_parent);
        }
    }
}

void FiboHeap::consolidate() //O(log(n))
{
    int size = (int)(log2(n));// / log2(1.618)); //size of tab ()
    Node** rank_tab = new Node*[size + 1];
    for(int i = 0; i < size + 1; i++) rank_tab[i] = nullptr; //initializing the tab
    int rank_index = 0; //index for tab (it's node's rank)

    Node* n = this->min_root;
    bool flag = false;
    while(true) //O(n+m)
    {
        rank_index = n->rank;
        while(rank_tab[rank_index] != nullptr)
        {
            Node* n2 = rank_tab[rank_index];
            if(n == n2) //we break the whole loop when all roots have different ranks
            {
                flag = true;
                break;
            }
            if(n->value > n2->value)
            {
                Node* temp = n;
                n = n2;
                n2 = temp;
            }
            std::cout << "\nn = " << n->value << " is n2 = " << n2->value << " father.\n";
            un_link(n2);
            n2->left = n2->right = n2;
            n2->parent = n;
            n->child = link(n->child, n2); //link child into parent's children
            n->rank++;
            n2->marked = false;
            rank_tab[rank_index++] = nullptr; //n node has one child more, so rank_tab[rank_index] = nullptr,  rank_index++
        }
        if(flag) break;
        rank_tab[n->rank] = n;
        n =  n->right;
    }
    this->min_root = n;
    Node* it = n;
    do                              //  O(log(n))
    {
       if(it->value < this->min_root->value) this->min_root = it;
       it = it->right;
    } while(it != n);
    delete rank_tab;
}

FiboHeap::Node *FiboHeap::find(FiboHeap::Node * n, int x) //function finds node by given x-value
{
    Node* found = nullptr;
    Node* tmp = n;
    tmp->V = 'Y';
    if(tmp->value == x)
    {
        found = tmp;
        tmp->V = 'N';
        return found;
    }
    if(tmp->child != nullptr) found = find(tmp->child, x);
    if(tmp->right->V != 'Y') found = find(tmp->right, x);
    tmp->V = 'N';
    return found;
}

void FiboHeap::create_test()
{
    Node* n1 = new Node;
    Node* n2 = new Node;
    Node* n3 = new Node;
    Node* n4 = new Node;
    n4->value = 10;
    n4->left = n4->right = n4;
    n4->parent = n3;
    n4->child = nullptr;
    n4->rank = 0;
    n4->marked = false;
    n4->V = 'N';

    n3->value = 7;
    n3->left = n3->right = n3;
    n3->parent = n2;
    n3->child = n4;
    n3->rank = 1;
    n3->marked = false;
    n3->V = 'N';

    n2->value = 5;
    n2->left = n2->right = n2;
    n2->parent = n1;
    n2->child = n3;
    n2->rank = 2;
    n2->marked = false;
    n2->V = 'N';

    this->min_root = n1;
    n1->value = 1;
    n1->left = n1->right = n1;
    n1->parent = nullptr;
    n1->child = n2;
    n1->rank = 3;
    n1->marked = false;
    n1->V = 'N';
    this->n = 4;
}
