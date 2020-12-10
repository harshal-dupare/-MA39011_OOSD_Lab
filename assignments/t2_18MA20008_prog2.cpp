#include <iostream>
#include <algorithm>

using namespace std;
class Node;

class llval
{
    public:
    Node* val;
    llval* next;
};
class queue
{
    llval* front=0;
    llval* rear=0;
    public:
    Node* pop_delete()
    {   
        Node* ret = front->val;
        llval* temp = front;
        front = front->next;
        delete temp;
        return ret;
    }
    Node* pop()
    {   
        return front->val;
    }

    void push(Node* val)
    {
        if(front==0)
        {
            front = rear = new llval();
            front->val = val;
            front->next = 0;
        }
        else if(front == rear)
        {
            rear = new llval();
            front->next = rear;
            rear->next = 0;
            rear->val = val;
        }
        else
        {
            llval* next = new llval();
            next->val = val;
            rear->next = next;
            rear = next;
            rear->next =0;
        }
    }
};

class Node
{
public:
    Node *left_child;
    Node *right_child;
    Node *parent;
    int val;
    int height;
    Node(Node *parent, int val) // default constructor. Initialize as a leaf node
    {
        this->parent = parent;
        left_child = 0;
        right_child = 0;
        this->height = 1;
        this->val = val;

    }
    int getBalance() // helper function to return balance of node
    {
        if (height == 1) // leaf
            return 0;
        if (!this->right_child) //one child
            return this->left_child->height;
        if (!this->left_child) //one child
            return -this->right_child->height;
        return this->left_child->height - this->right_child->height; //two child
    }
    void updateHeight(int inc = 0) // helper function to update height
    {
        if (!(this->left_child || this->right_child)) // leaf
            this->height = 1;
        else if (!this->right_child) // 1 child
            this->height = this->left_child->height + inc;
        else if (!this->left_child) // 1 child
            this->height = this->right_child->height + inc;
        else // 2 children
            this->height = max(this->right_child->height, this->left_child->height) + inc;
    }
    Node *&getChildRef(Node *expected) // helper function to return the reference to which children of the parent the given node is
    {
        if (left_child == expected)
            return this->left_child;
        else
            return this->right_child;
    }
};

//This class stores the tree as head node and then provides functions for operations on the tree
class MinHeap
{
private:
    int size = 0;
    queue qu;
    void rebalance(Node* c_node) // top down for deletion 
    {
        if(!c_node) return;
        int l = c_node->val;
        Node*& li = c_node;
        Node*& sw = c_node;
        if (c_node->left_child && l > c_node->left_child->val)
            l =c_node->left_child->val, li = c_node->left_child;
        if (c_node->right_child && l > c_node->right_child->val)
            l = c_node->right_child->val, li = c_node->right_child;
        if (li!=c_node)
        {
            swap(li->val, c_node->val);
            rebalance(li);
        }
    }
    void heapify(Node* & c_node)
    {
        if(!c_node) return;
        if(c_node->parent)
        {
            if(c_node->val < c_node->parent->val)
            {
                swap(c_node->val, c_node->parent->val);
                heapify(c_node->parent);
            }
        }
    }
    void insert(int val, bool flag) // private function to insert a number
    {
        Node* last_node = qu.pop();
        if(!last_node->left_child)
        {
            last_node->left_child = new Node(last_node, val);
            last_node->left_child->parent = last_node;
            qu.push(last_node->left_child);
        }
        else if(!last_node->right_child)
        {
            last_node->right_child = new Node(last_node, val);
            last_node->right_child->parent = last_node;
            qu.push(last_node->right_child);
        }
        else
        {
            qu.pop_delete();
            insert(val, 0);
        }
    }
    void printSorted(Node *cnode) // helper function to print in sorted order from given node
    {
        if (cnode->left_child)
            printSorted(cnode->left_child);
        cout << " " << cnode->val;
        if (cnode->right_child)
            printSorted(cnode->right_child);
    }

public:
    Node *head;
    Node *last_elem;
    MinHeap() // default empty constructor
    {
        head = 0;
    }

    void print() // print tree in sorted order
    {
        cout << "In Order: ";
        printSorted(head);
        cout << "\n";
    }

    void insert(int val) // insert a value from the tree
    {
        if (!head)
        { // handle empty tree
            head = new Node(0, val);
            qu.push(head);
        }
        else
            insert(val, 0);
    }

    void remove() // remove a value from the tree
    {
        if(!head) // handle empty tree
            cout << "Empty tree!\n";
        else
           {
               Node* ll = qu.pop();
               ll->parent->getChildRef(ll) = 0;
               swap(head->val, ll->val);
               rebalance(head);
               delete ll;
           }
    }


};

int main()
{
    MinHeap tree;
    while(1) // main loop
    {
        cout << "Use a to add a number, r to remove a number, s to print in order the tree, q to quit. \n"; // user prompt
        char c;
        cin >> c;
        if(c=='a') // add a number to the tree
        {
            cout << "Type number: ";
            int x;
            cin >> x;
            tree.insert(x); // function call
        }
        else if(c=='r') // remove a number from the tree
        {
            tree.remove(); // function call
        }
        else if(c=='s') // print in sorted order
        {
            tree.print();
        }
        else if(c=='q') // quit from loop
            break;
        else // valid check
            cout << "Invalid Input!\n";
    }

}