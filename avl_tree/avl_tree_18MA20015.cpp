#include <iostream>
#define INF 1000007
using namespace std;

// utility function max
int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

// struct to stor the avl node
struct avl_node
{
    int data;
    avl_node *left;
    avl_node *right;
    int height;
};

// AVL tree class
class AVL
{
public:
    // root node
    avl_node *root = NULL;
    int size = 0;

    // function to get new avl node
    avl_node *new_avl_node(int data)
    {
        avl_node *new_node = new avl_node();
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->data = data;
        new_node->height = 1;
        return new_node;
    }

    // returns the minimum value node from the tree
    avl_node *min_value_node(avl_node *node)
    {
        // if no node then return null
        if (node == NULL)
            return NULL;

        // find the leftmost node
        avl_node *temp = node;
        while (temp->left != NULL)
            temp = temp->left;
        return temp;
    }

    // function to get the hight of node
    int get_height(avl_node *r)
    {
        if (r == NULL)
            return 0;
        return r->height;
    }

    // function to update the hight
    void update_height(avl_node *node)
    {
        if (node == NULL)
            return;
        // max of left height and right height + 1
        node->height = 1 + max(get_height(node->left), get_height(node->right));
    }

    // returns the balance factor of node
    int get_balance(avl_node *node)
    {
        if (node == NULL)
            return 0;
        return get_height(node->left) - get_height(node->right);
    }

    // right rotate the node
    avl_node *right_rotate(avl_node *node)
    {
        avl_node *son_node = node->left;
        avl_node *gson_node = son_node->right;

        son_node->right = node;
        node->left = gson_node;

        update_height(node);
        update_height(son_node);

        return son_node;
    }

    // left rotate the node
    avl_node *left_rotate(avl_node *node)
    {
        avl_node *son_node = node->right;
        avl_node *gson_node = son_node->left;

        son_node->left = node;
        node->right = gson_node;

        update_height(node);
        update_height(son_node);

        return son_node;
    }

    // function to insert the node
    avl_node *insert(int data, avl_node *node)
    {
        // if node in null return the new node with data
        if (node == NULL)
            return new_avl_node(data);

        if (data < node->data)
            node->left = insert(data, node->left);
        else if (data > node->data)
            node->right = insert(data, node->right);
        else
            return node; // node with same value is not allowed

        // updating the hight of node
        update_height(node);

        // checking if this node becomes imbalance or not and handeling the cases
        int balance = get_balance(node);

        // case 1
        /*
               x
              /
             y
            /
           z
        */
        if (balance > 1 && data < node->left->data)
            return right_rotate(node);

        // case 2
        /*
               x
                \
                 y
                  \
                   z
        */
        if (balance < -1 && data > node->right->data)
            return left_rotate(node);

        // case 3
        /*
                   x
                  /
                 y
                  \
                   z
        */
        if (balance > 1 && data > node->left->data)
        {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        // case 4
        /*
                   x
                    \
                     y
                    /
                   z
        */
        if (balance < -1 && data < node->right->data)
        {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        this->size++;
        return node;
    }

    // delete the node
    avl_node *delete_node(avl_node *root, int data)
    {
        // the data value is not there in tree
        if (root == NULL)
        {
            cout << "Given node doesn't exist in the tree!" << endl;
            return root;
        }

        // going to the root which has the data value
        if (data < root->data)
            root->left = delete_node(root->left, data);
        else if (data > root->data)
            root->right = delete_node(root->right, data);
        else
        {
            // only 1 or 0 child
            if ((root->left == NULL) || (root->right == NULL))
            {
                avl_node *temp = NULL;
                if (root->left == NULL)
                    temp = root->right;
                else
                    temp = root->left;

                // if there is no child
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
            }
            else
            {
                // both the children are there hence get the min value node
                avl_node *temp = min_value_node(root->right);
                // copy the data to this node
                root->data = temp->data;
                // delete this min node
                root->right = delete_node(root->right, temp->data);
            }
        }

        // if only 1 node then delete and return
        if (root == NULL)
            return root;

        // update the height before calculating the balance factor
        update_height(root);

        // check the balance factor and handel the cases
        int balance = get_balance(root);

        // case 1
        /*
               x
              /
             y
            /
           z
        */
        // if height or left is larger than right by more than 1 then need to do a right rotation
        if (balance > 1 && get_balance(root->left) >= 0)
            return right_rotate(root);

        // case 2
        /*
               x
                \
                 y
                  \
                   z
        */
        // if height or left is larger than right by more than 1 but of the left child has right height larger then need to do a left-right rotation
        if (balance > 1 && get_balance(root->left) < 0)
        {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }

        // case 3
        /*
                   x
                  /
                 y
                  \
                   z
        */
        // if height or right is larger right by more than 1 then need to do a right rotation
        if (balance < -1 && get_balance(root->right) <= 0)
            return left_rotate(root);

        // case 4
        /*
                   x
                    \
                     y
                    /
                   z
        */
        // if height or right is larger than left by more than 1 but of the right child had left height larger then need to do a left-right rotation
        if (balance < -1 && get_balance(root->right) > 0)
        {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }

        this->size--;
        return root;
    }

    // prints the elements of tree in order
    void in_order_printing(avl_node *root)
    {
        if (root != NULL)
        {
            in_order_printing(root->left);
            cout << root->data << " ";
            in_order_printing(root->right);
        }
    }

    // from the given avl tree we create the heap by filling the empty locations wrt heap by  INF
    // it has recursive function implementation
    void make_heap(avl_node *root, int *a, int k)
    {
        // if node is not null then we need to insert it into the heap
        if (root != NULL)
        { // first insert all of its left subtree
            make_heap(root->left, a, (k << 1));
            // insert the node into right location in heap
            a[k - 1] = root->data;
            // then insert the right subtree
            make_heap(root->right, a, ((k << 1) + 1));
        }
    }

    // main function to print the AVL tree
    void print_tree(AVL tree)
    {
        // if tree is empty
        if (tree.root == NULL)
        {
            cout << "Tree is empty!" << endl;
            return;
        }

        // if not empty then get the hight and calculate the size of heap required to store the tree
        int h = tree.root->height;
        // size of heap required = 2^(height+1)-1 <= 2^(height+1)
        int n = 1 << (h + 1);
        // array to store the heap
        int ar[n];
        for (int i = 0; i < n; i++)
        {
            ar[i] = INF;
        }

        // making the heap
        make_heap(tree.root, ar, 1);

        // tph stores the hight at which we are printing the tree
        int tph = 0;
        // gap is the size of blankspaces to print between two nodes
        int gap = 1 << (h + 1);

        // we loop over all the hights and print all the nodes in it
        while (tph <= h)
        {

            int j = (1 << (tph + 1)) - 1; // start index of height
            int i = (1 << (tph)) - 1;     // end index of height
            for (; i < j; i++)
            {
                // printing the gap-1 size of blankspace
                for (int k = 0; k < gap - 1; k++)
                {
                    cout << " ";
                }

                // if the locatons is other than INF then print the number else print blankspace
                if (ar[i] != INF)
                    cout << ar[i];
                else
                    cout << " ";

                // printing the gap size of blankspace
                for (int k = 0; k < gap; k++)
                {
                    cout << " ";
                }
            }
            gap >>= 1; // decrease the gap by half
            cout << endl
                 << endl;
            tph++; // go to next height
        }
    }
};

int main()
{
    AVL tree = AVL(); // avl tree in stored in this
    int i, c;
    // main while loop
    while (true)
    {
        // input specifications
        cout << "1> Insert element" << endl;
        cout << "2> Delete node" << endl;
        cout << "3> Print tree elements in inorder" << endl;
        cout << "4> Print tree in tree shape " << endl;
        cout << "5> Sort an array using the AVL tree " << endl;
        cout << "6> Exit" << endl;
        cout << "Enter your choice: ";
        cin >> c;
        if (c == 1)
        {
            // inserting the node
            cout << endl;
            cout << "Enter Distinct value to be inserted: ";
            cin >> i;
            tree.root = tree.insert(i, tree.root);
            cout << endl;
        }
        else if (c == 2)
        {
            // deleting the node
            if (tree.root == NULL)
            {
                cout << endl;
                cout << "There is no element to delete" << endl;
                cout << endl;
                continue;
            }
            cout << endl;
            cout << "Enter value to be deleted: ";
            cin >> i;
            tree.root = tree.delete_node(tree.root, i);
            cout << endl;
        }
        else if (c == 3)
        {
            // printing in order all the elements of tree
            cout << endl;
            cout << "Printing the elements of tree in order ( sorted way ):" << endl;
            tree.in_order_printing(tree.root);
            cout << endl;
            cout << endl;
        }
        else if (c == 4)
        {
            // print the tree
            cout << endl;
            cout << "Printing the tree in tree shape" << endl;
            tree.print_tree(tree);
            cout << endl;
        }
        else if (c == 5)
        {
            // take input of elements to sort using avl tree in nlog(n) time
            int n;
            cout << endl;
            cout << " Enter the number of elements in array you want to sort: ";
            cin >> n;
            if (n <= 0)
                continue;
            cout << " Enter the " << n << " distinct numbers in array to sort: " << endl;
            AVL tree2 = AVL();
            for (int k = 0; k < n; k++)
            {
                int tp;
                cin >> tp;
                tree2.root = tree2.insert(tp, tree2.root);
            }
            cout << "Sorted array is :" << endl;
            tree2.in_order_printing(tree2.root);
            cout << endl;
            cout << endl;
        }
        else if (c == 6)
        {
            // exit
            exit(1);
        }
        else
        {
            cout << endl;
            cout << "Incorrect input, please give proper input!" << endl;
            cout << endl;
        }
    }
    return 0;
}