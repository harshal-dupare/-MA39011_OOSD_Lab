/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Date : 8-11-2020
Time complexity : O(nlogn)
Space complexity : O(n)
Method : y monotone dec
*/


#include <iostream>
#include <graphics.h>
#include <X11/Xlib.h>
#include <string>
#define EPS 1e-8
#define FINF 1e+8

using namespace std;

#define OK(x) cout << #x << " : " << x << " " << endl;

enum point_type
{
    startv,
    endv,
    regularv,
    splitv,
    mergev
};

string ptypec[] = {"startv", "endv", "regularv", "splitv", "mergev"};

class point
{
public:
    double x;
    double y;
    int index;
    double r2;
    double costhita;
    point *last;
    point *next;
    point_type ptype;
    point()
    {
        x = 0;
        y = 0;
        index = 0;
        r2 = 0;
        costhita = -2;
        last = nullptr;
        next = nullptr;
        ptype = regularv;
    }
    point(double x, double y, int index)
    {
        this->x = x;
        this->y = y;
        this->index = index;
        this->r2 = x * x + y * y;
        if (this->r2 > EPS)
            this->costhita = x / this->r2;
        else
            this->costhita = -2;

        this->next = nullptr;
        this->last = nullptr;
        this->ptype = regularv;
    }
    void set(double x, double y, int index)
    {
        this->x = x;
        this->y = y;
        this->index = index;
        this->r2 = x * x + y * y;
        if (this->r2 > EPS)
            this->costhita = x / this->r2;
        else
            this->costhita = -2;

        this->next = nullptr;
        this->last = nullptr;
        this->ptype = regularv;
    }

    // returns true if the point other is adj to this point else false
    bool adj(point *other)
    {
        if (other == this->last || other == this->next)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // same as span interior but also checks for the orientation
    int span_interior_spl(point *last, point *next, int &orient)
    {
        OK(orient)
        last->show();
        next->show();
        this->show();
        if (orient == 0)
        {
            if (last == this->last)
            {
                orient = -1;
                return this->span_interior((*last), (*next));
            }
            else
            {
                orient = 1;
                return this->span_interior((*next), (*last));
            }
        }
        else if (orient == 1) // anticlockwise
        {
            return this->span_interior((*next), (*last));
        }
        else // if orient == -1 , clockwise
        {
            return this->span_interior((*last), (*next));
        }
    }

    // returns 1 if this comes before other -1 if other before this and else 0
    int before(point &other)
    {
        if (abs(this->y - other.y) < EPS)
        {
            int k = 0;
            if (this->x < other.x)
            {
                k = 1;
            }
            else
            {
                k = -1;
            }

            return k;
        }
        else if (this->y > other.y)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    void operator&=(point &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->r2 = other.r2;
        this->index = other.index;
        this->costhita = other.costhita;
        this->ptype = other.ptype;
        this->last = other.last;
        this->next = other.next;
    }

    bool operator<=(point &other)
    {
        // this->show();
        // other.show();
        if (this->before(other) == -1)
        {
            // OK("before\n");
            return false;
        }
        else
        {
            // OK("after\n");
            return true;
        }
    }

    // O(1) time
    // returns distance square of this point from point a
    double dist_square(point &a)
    {
        double d2 = (a.x - this->x) * (a.x - this->x) + (a.y - this->y) * (a.y - this->y);
        return d2;
    }

    // O(1) time
    // Distance from line ---p1----p2----
    double dist_line(point &p1, point &p2)
    {
        double delta = abs((p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y));
        return delta;
    }

    // O(1) time
    int span_interior(point &last, point &next)
    {
        double v1x = this->x - last.x;
        double v1y = this->y - last.y;
        double v2x = next.x - this->x;
        double v2y = next.y - this->y;

        double cross_product = v1x * v2y - v1y * v2x;

        if (abs(cross_product) <= EPS)
            return 0; // i.e. if all points are on a line i.e. crossproduct is zero

        if (cross_product > 0.0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    // O(1) time
    // returns 1 if in the segment , 0 if on the line contaning the segment, else -1
    int in_segment(point &p1, point &p2)
    {
        double delta = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);

        // not on line
        // OK(delta)
        if (abs(delta) > EPS)
        {
            return -1;
        }

        // if on line then need to check if inside the segment

        int sign_p1x, sign_p2y, sign_p2x, sign_p1y;
        double temp;
        temp = this->x - p1.x;
        if (abs(temp) <= EPS)
            sign_p1x = 0;
        else if (temp > 0)
            sign_p1x = 1;
        else
            sign_p1x = -1;

        temp = this->y - p1.y;
        if (abs(temp) <= EPS)
            sign_p1y = 0;
        else if (temp > 0)
            sign_p1y = 1;
        else
            sign_p1y = -1;

        temp = this->x - p2.x;
        if (abs(temp) <= EPS)
            sign_p2x = 0;
        else if (temp > 0)
            sign_p2x = 1;
        else
            sign_p2x = -1;

        temp = this->y - p2.y;
        if (abs(temp) <= EPS)
            sign_p2y = 0;
        else if (temp > 0)
            sign_p2y = 1;
        else
            sign_p2y = -1;

        int side;
        // if(this->x==4&&this->y==4)
        // {
        //     cout<<endl;
        //     OK(sign_p1x)
        //     OK(sign_p1y)
        //     OK(sign_p2x)
        //     OK(sign_p2y)
        // }

        if (!(sign_p1x == 0 || sign_p2x == 0))
        {
            int vote_x = sign_p1x * sign_p2x;
            if (vote_x == -1)
            {
                // if point is in the segment
                side = 1;
            }
            else
            {
                // if point is not in the segment but on the line
                side = 0;
            }

            return side;
        }
        else if (!(sign_p1y == 0 || sign_p2y == 0))
        {
            int vote_y = sign_p1y * sign_p2y;
            if (vote_y == -1)
            {
                // if point is in the segment
                side = 1;
            }
            else
            {
                // if point is not in the segment but on the line
                side = 0;
            }
            return side;
        }
        else
        {
            side = 0;
        }

        return side;
    }

    // O(1) time
    // 1, if on same side
    // 0, if any of a or this on the line p1--p2
    // -1, if not on the same side
    int on_same_side(point &a, point &p1, point &p2)
    {
        /*
        line is formed by p1 and p2
        (p1x -p2x)(y-p1y) - (x-p1x)(p1y-p2y) = 0 if on line else > 0 or < 0 tells the side of line
        the function returns 1 if both on same side 0 if anyone on the line and -1 if both on different side
        */
        double delta_a = (p1.x - p2.x) * (a.y - p1.y) - (a.x - p1.x) * (p1.y - p2.y);
        double delta_this = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);
        int sgn_a = 0, sgn_this = 0;
        if (abs(delta_a) <= EPS)
            sgn_a = 0;
        else if (delta_a > 0)
            sgn_a = 1;
        else
            sgn_a = -1;

        if (abs(delta_this) <= EPS)
            sgn_this = 0;
        else if (delta_this > 0)
            sgn_this = 1;
        else
            sgn_this = -1;

        if (sgn_a == 0 || sgn_this == 0)
            return 0;
        if (sgn_a == sgn_this)
            return 1;
        else
            return -1;
    }

    // O(1) time
    // -1, if not on the triangle
    // 0, if on the triangle ( segments of the triangle )
    // 1, in the triangle but not on it
    int in_triangle(point &a, point &b, point &c)
    {
        int abc, bca, cab;
        abc = this->on_same_side(a, b, c);
        bca = this->on_same_side(b, c, a);
        cab = this->on_same_side(c, a, b);
        int sign_bc = this->in_segment(b, c);
        int sign_ca = this->in_segment(c, a);
        int sign_ab = this->in_segment(a, b);
        // if(this->x==4&&this->y==4)
        // {
        //     cout<<endl;
        //     OK(abc)
        //     OK(bca)
        //     OK(cab)
        //     OK(sign_ab)
        //     OK(sign_bc)
        //     OK(sign_ca)
        // }

        // if all are 1 then its in the triangle
        if (abc == 1 && bca == 1 && cab == 1)
        {
            return 1;
        }

        // if on the other side of any line then its not in/on the triangle
        if ((abc == -1) || (bca == -1) || (cab == -1))
        {
            return -1;
        }

        // if on any of the lines then need to check if inside thesegment or not
        if (abc == 0)
        {
            if (sign_bc == 1)
            {
                // if in the segment bc
                return 0;
            }
            else
            {
                // on the line containg segment bc
                return -1;
            }
        }
        else if (bca == 0)
        {
            if (sign_ca == 1)
            {
                // if in the segment ca
                return 0;
            }
            else
            {
                // on the line containg segment ca
                return -1;
            }
        }
        else
        {
            if (sign_ab == 1)
            {
                // if in the segment ab
                return 0;
            }
            else
            {
                // on the line containg segment ab
                return -1;
            }
        }

        return 1;
    }

    // sets the type of point
    void set_point_type(point &last, point &next)
    {
        int sgn = this->span_interior(last, next);
        if (last.y > this->y)
        {
            if (next.y >= this->y)
            {
                // both neighbour points above the point
                if (sgn == -1)
                {
                    // angle less than pi
                    this->ptype = endv;
                }
                else
                {
                    // angle more than pi
                    this->ptype = mergev;
                }
            }
            else
            {
                this->ptype = regularv;
            }
        }
        else
        {
            if (next.y > this->y)
            {
                this->ptype = regularv;
            }
            else
            {
                // both neighbour points below the point
                if (sgn == -1)
                {
                    // angle less than pi
                    this->ptype = startv;
                }
                else
                {
                    // angle more than pi
                    this->ptype = splitv;
                }
            }
        }
    }

    void show()
    {
        cout << "(" << x << "," << y << ") ";
        return;
    }
};

class node
{
public:
    point *p;
    int index;
    node *next = nullptr;
    node *last = nullptr;

    node();

    node(int index)
    {
        this->index = index;
        p = new point();
    }

    void operator&=(const node &other)
    {
        this->index = other.index;
        this->p = other.p;
        this->next = other.next;
        this->last = other.last;
    }
};

class onode
{
public:
    node *nd;
    int index;
    node *next = nullptr;
    node *last = nullptr;

    onode()
    {
        this->nd = nullptr;
    }

    onode(int index)
    {
        this->index = index;
        this->nd = nullptr;
    }

    onode(int index, node *nd)
    {
        this->index = index;
        this->nd = nd;
    }

    void operator&=(const onode &other)
    {
        this->index = other.index;
        this->nd = other.nd;
        this->next = other.next;
        this->last = other.last;
    }

    bool operator<=(onode &other)
    {
        point p1 = *this->nd->p;
        point p2 = *other.nd->p;
        return p1 <= p2;
    }
};

class edge
{
public:
    node *top;
    node *bottom;
    node *helper;

    edge()
    {
        top = nullptr;
        bottom = nullptr;
        helper = nullptr;
    }

    // constructor
    edge(node *top, node *bottom, node *helper)
    {
        this->top = top;
        this->bottom = bottom;
        this->helper = helper;
    }

    // calculates the x loaction on the this edge where its y coordiante is other_y
    double xaty(double other_y)
    {
        double deltax = (top->p->x - bottom->p->x);
        double deltay = (top->p->y - bottom->p->y);
        double inverse_slope = deltax / deltay;

        double ans = (other_y - top->p->y) * inverse_slope + top->p->x;

        return ans;
    }

    // returns true if this edge is to the left of the other edge
    bool to_left(edge other)
    {
        double xloc_other = this->xaty(other.top->p->y);
        if ((abs(xloc_other - other.top->p->x) <= EPS) || (xloc_other < other.top->p->x))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // returns true if this edge is to the right of the other edge
    bool to_right(edge other)
    {
        double xloc_other = this->xaty(other.top->p->y);
        if ((abs(xloc_other - other.top->p->x) <= EPS) || (xloc_other > other.top->p->x))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // returns true if this and other edge represent the same edge
    bool is_same(edge *other)
    {
        if (this->bottom == other->bottom && this->top == other->top)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void operator&=(const edge &other)
    {
        this->top = other.top;
        this->bottom = other.bottom;
        this->helper = other.helper;
    }

    void print()
    {
        char cc1 = (this->top->p->index + 'A');
        char cc2 = (this->bottom->p->index + 'A');
        char cc3 = (this->helper->p->index + 'A');
        cout << "(" << cc1 << "," << cc2 << ")->[" << cc3 << "] ";
    }
};

class container
{
public:
    point *p;

    container *next;
    container *last;

    container()
    {
        this->p = nullptr;
        this->next = nullptr;
        this->last = nullptr;
    }

    container(point *p, container *next, container *last)
    {
        this->p = p;
        this->next = next;
        this->last = last;
    }
};

class stack
{
public:
    container *top;
    container *bottom;
    int size;

    stack()
    {
        top = nullptr;
        bottom = nullptr;
        size = 0;
    }

    void push(point *p)
    {
        if (this->size == 0)
        {
            container *x = new container(p, nullptr, nullptr);
            this->top = x;
            this->bottom = x;
            size++;
            return;
        }
        container *x = new container(p, this->top, nullptr);
        this->top->last = x;
        this->top = x;
        this->size++;
    }

    void pop()
    {
        if (this->size == 0)
        {
            return;
        }
        this->top = this->top->next;
        if (this->top != nullptr)
            this->top->last = nullptr;
        this->size--;
    }
};

#define INF 1000007

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
    // int data;
    edge data;
    avl_node *left;
    avl_node *right;
    int height;
};

// AVL tree class
class AVL
{
public:
    // root node
    avl_node *root = nullptr;
    int size = 0;

    // function to get new avl node
    avl_node *new_avl_node(edge data)
    {
        avl_node *new_node = new avl_node();
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->data = data;
        new_node->height = 1;
        return new_node;
    }

    // returns the minimum value node from the tree
    avl_node *min_value_node(avl_node *node)
    {
        // if no node then return nullptr
        if (node == nullptr)
            return nullptr;

        // find the leftmost node
        avl_node *temp = node;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    // function to get the hight of node
    int get_height(avl_node *r)
    {
        if (r == nullptr)
            return 0;
        return r->height;
    }

    // function to update the hight
    void update_height(avl_node *node)
    {
        if (node == nullptr)
            return;
        // max of left height and right height + 1
        node->height = 1 + max(get_height(node->left), get_height(node->right));
    }

    // returns the balance factor of node
    int get_balance(avl_node *node)
    {
        if (node == nullptr)
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
    avl_node *insert(edge data, avl_node *node)
    {
        // if node in nullptr return the new node with data
        if (node == nullptr)
        {
            this->size++;
            avl_node *temp = new_avl_node(data);
            temp->data.print();
            cout << endl;
            return temp;
        }

        if (!node->data.to_left(data))
            node->left = insert(data, node->left);
        else if (node->data.to_left(data))
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
        if (balance > 1 && (!node->left->data.to_left(data)))
            return right_rotate(node);

        // case 2
        /*
               x
                \
                 y
                  \
                   z
        */
        if (balance < -1 && (!data.to_left(node->right->data)))
            return left_rotate(node);

        // case 3
        /*
                   x
                  /
                 y
                  \
                   z
        */
        if (balance > 1 && node->left->data.to_left(data))
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
        if (balance < -1 && (!node->right->data.to_left(data)))
        {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    // delete the node
    avl_node *delete_node(avl_node *root, edge data)
    {
        // the data value is not there in tree
        if (root == nullptr)
        {
            cout << "Given node doesn't exist in the tree!" << endl;
            return root;
        }

        // going to the root which has the data value
        if (root->data.is_same(&data))
        {
            // this node has the data edge
            // only 1 or 0 child
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                avl_node *temp = nullptr;
                if (root->left == nullptr)
                    temp = root->right;
                else
                    temp = root->left;

                // if there is no child
                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
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
        else if (!root->data.to_left(data))
            root->left = delete_node(root->left, data);
        else if (root->data.to_left(data))
            root->right = delete_node(root->right, data);

        // if only 1 node then delete and return
        if (root == nullptr)
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

        return root;
    }

    // returns the edge which is the left to this node
    // log(n) time
    edge *get_leftedge(onode *ond)
    {
        edge *best_edge = nullptr;
        double best_dist = FINF;

        avl_node *temp = this->root;
        while (temp != nullptr)
        {
            double ond_xaty = temp->data.xaty(ond->nd->p->y);
            if (ond_xaty <= ond->nd->p->x)
            {
                double dist = ond->nd->p->x - ond_xaty;
                if (best_dist >= dist)
                {
                    best_dist = dist;
                    best_edge = &temp->data;
                }
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        return best_edge;
    }

    // log(n) time
    edge *get_topedge(onode *ond)
    {
        edge *best_edge = nullptr;
        // double best_dist = FINF;

        avl_node *temp = this->root;
        while (temp != nullptr)
        {
            double ond_xaty = temp->data.xaty(ond->nd->p->y);
            // if (ond_xaty <= ond->nd->p->x)
            // {
            //     double dist = ond->nd->p->x - ond_xaty;
            //     if (best_dist >= dist)
            //     {
            //         best_dist = dist;
            //         best_edge = &temp->data;
            //     }
            //     temp = temp->right;
            // }
            // else
            // {
            //     temp = temp->left;
            // }

            if (abs(ond_xaty - ond->nd->p->x) <= (5 * EPS) || (temp->data.bottom == ond->nd))
            {
                best_edge = &temp->data;
                return best_edge;
            }
            else if (ond_xaty < ond->nd->p->x)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        return best_edge;
    }

    // prints the elements of tree in order
    void in_order_printing(avl_node *root)
    {
        if (root != nullptr)
        {
            in_order_printing(root->left);
            root->data.print();
            in_order_printing(root->right);
        }
    }

    // from the given avl tree we create the heap by filling the empty locations wrt heap by  INF
    // it has recursive function implementation
    void make_heap(avl_node *root, edge *a, int k)
    {
        // if node is not nullptr then we need to insert it into the heap
        if (root != nullptr)
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
        if (tree.root == nullptr)
        {
            cout << "Tree is empty!" << endl;
            return;
        }

        // if not empty then get the hight and calculate the size of heap required to store the tree
        int h = tree.root->height;
        // size of heap required = 2^(height+1)-1 <= 2^(height+1)
        int n = 1 << (h + 1);
        // array to store the heap
        edge ar[n];
        for (int i = 0; i < n; i++)
        {
            ar[i].top = nullptr;
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
                if (ar[i].top != nullptr)
                    ar[i].print();
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

// for sorting array of points in nlogn time
void merge_node(onode arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    onode *L = new onode[n1];
    onode *R = new onode[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;

    int j = 0;

    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    return;
}

// for sorting array of points in nlogn time
void mergeSort_node(onode arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort_node(arr, l, m);
        mergeSort_node(arr, m + 1, r);

        merge_node(arr, l, m, r);
    }
    return;
}

class circular_linked_list
{
public:
    node *head;
    int n;
    circular_linked_list()
    {
        this->head = nullptr;
        this->n = 0;
    }
    // O(n) time
    // constructor which creates the linked list fromthe points in ps[][2];
    circular_linked_list(int n, double ps[][2])
    {
        // if no points then return by making head nullptr and n = 0
        if (n == 0)
        {
            this->n = 0;
            this->head = nullptr;
            return;
        }

        // if there are some points
        int i = 0;
        this->n = n;

        // we go through all the points and make new nodes to hold these point and repeat till all points are allocated
        head = new node(i);
        head->p = new point(ps[i][0], ps[i][1], i);
        node *temp = head;
        i++;
        while (i < n)
        {
            temp->next = new node(i);                         //next pointer
            temp->next->p = new point(ps[i][0], ps[i][1], i); // next node data is filled
            temp->next->last = temp;                          // last of the next must point to temp node itself( i.e. the node we are on)

            temp->next->p->last = (temp->p);
            temp->p->next = (temp->next->p);
            temp = temp->next; // going to the next node created just now
            i++;
        }
        temp->next = head; // at the end the last node must point to head
        temp->p->next = (head->p);
        head->last = temp; // and head must point the the last node using last pointer
        head->p->last = (temp->p);

        // set the point type for all the points in the list
        temp = head;
        do
        {
            temp->p->set_point_type(*(temp->p->last), *(temp->p->next));
            temp = temp->next;
        } while (temp != head);
    }

    // O(n) time
    // splits this list into 2 lists across node x and node y which must be in the liked list
    // allocates this 2 lists to lxy and lyx
    void split(node *x, node *y, circular_linked_list &lxy, circular_linked_list &lyx)
    {
        node *newx = new node(x->index);
        // connecting the new x node to the the last of x
        newx->last = x->last;
        x->last->next = newx;
        newx->p = new point(x->p->x, x->p->y, x->index);

        node *newy = new node(y->index);
        // connecting the new x node to the the next of y
        newy->next = y->next;
        y->next->last = newy;
        newy->p = new point(y->p->x, y->p->y, x->index);

        // connecting new x and new y
        newx->next = newy;
        newy->last = newx;

        // connecting  x and y
        y->next = x;
        x->last = y;

        // updating the heads of the new circular lists
        lxy.head = x;
        lxy.n = lxy.count();
        lyx.head = newy;
        lyx.n = lyx.count();
    }

    // O(n) time
    // counts the number of nodes in this list and returns the count
    int count()
    {
        node *temp = this->head;

        // if head is nullptr then return 0
        if (temp == nullptr)
            return 0;

        // else vist each node and increase the count
        int ct = 0; // count
        do
        {
            ct++;
            temp = temp->next;
        } while (temp != this->head);
        // terminate the loop once we reach back to the head node

        return ct;
    }

    // O(n) time
    // prints the list
    void print()
    {
        node *temp = this->head;
        if (temp == nullptr)
        {
            cout << "Empty List" << endl;
            return;
        }

        do
        {
            temp->p->show();
            cout << " : ptype : " << ptypec[temp->p->ptype] << endl;
            temp = temp->next;
        } while (temp != this->head);

        return;
    }
};

class polygon
{
public:
    int n;
    circular_linked_list points;

    polygon()
    {
        this->n = 0;
    }
    void set(int n, double ps[][2])
    {
        points = circular_linked_list(n, ps);
        this->n = n;
    }
    polygon(int n, double ps[][2])
    {
        points = circular_linked_list(n, ps);
        this->n = n;
    }

    // split the polygon into 2 polygons across x and y and allocate them to p1 and p2
    void split(node *x, node *y, polygon &p1, polygon &p2)
    {
        points.split(x, y, p1.points, p2.points);
        p1.n = p1.points.n;
        p2.n = p2.points.n;
    }

    // utility function to print the polygon
    void show()
    {
        points.print();
        cout << endl;
    }
};

void decompose_polygon(polygon &p, node *temp1[], node *temp2[], int &at, int t[][2])
{
    if (p.n <= 3)
    {
        return;
    }
    int n = p.n;

    // copy and sort the polygon points
    onode *arr = new onode[n];

    node *start = p.points.head;
    int i = 0;
    do
    {
        arr[i].nd = start;
        arr[i].index = start->index;
        arr[i].next = start->next;
        arr[i].last = start->last;
        start = start->next;
        i++;
    } while (start != p.points.head);

    // sets the order in which to visit each vertex
    mergeSort_node(arr, 0, n - 1);

    // tree to store the active edges and their helper
    AVL edge_tree = AVL();

    // main loop to go through each vertex and identify its type and act accordingly
    for (int i = 0; i < n; i++)
    {

        if (arr[i].nd->p->ptype == startv)
        {
            edge tmpedg = edge(arr[i].nd, arr[i].nd->last, arr[i].nd);
            // insert the left adj edges in the tree
            edge_tree.root = edge_tree.insert(tmpedg, edge_tree.root);
            // for the left edge make this vertex as helper
        }
        else if (arr[i].nd->p->ptype == endv)
        {
            // since the next node just above is in the tree then we process the helper of this edge as we are gonna delete this edge
            // need left edge to get the helper
            edge *topedge = edge_tree.get_topedge(&arr[i]); // returns pointer to the node which has the helper vertex
            OK((topedge == nullptr))
            if (topedge->helper->p->ptype == mergev)
            {
                OK(ptypec[topedge->helper->p->ptype])
                // we connect only if the helper vertex is merge vertex
                temp1[at] = arr[i].nd;
                t[at][0] = arr[i].nd->p->index;
                temp2[at] = topedge->helper;
                t[at][1] = topedge->helper->p->index;
                at++;

                // delete the leftedge from the tree
                edge_tree.root = edge_tree.delete_node(edge_tree.root, *topedge);
            }
        }
        else if (arr[i].nd->p->ptype == regularv)
        {
            // if regular vertex then there is an active edge whihc end on this vertex
            // also this vertex must have the next node above it hence we check that and only then process it
            if (arr[i].next->p->y > arr[i].nd->p->y)
            {
                // if polygon is on the right side of the regular edge
                // only then the both the top and bottom edge can be in the edge tree
                edge *topedge = edge_tree.get_topedge(&arr[i]); // returns pointer to the node which has the helper vertex

                // this returns the edge in the tree which has bottom as this vertex

                if (topedge->helper->p->ptype == mergev)
                {
                    // we connect only if the helper vertex is merge vertex
                    temp1[at] = arr[i].nd;
                    t[at][0] = arr[i].nd->p->index;
                    temp2[at] = topedge->helper;
                    t[at][1] = topedge->helper->p->index;
                    at++;
                }

                edge_tree.root = edge_tree.delete_node(edge_tree.root, *topedge);

                //the new bottom edge
                edge tmpedg = edge(arr[i].nd, arr[i].nd->last, arr[i].nd);

                // insert the new bottom edge
                edge_tree.root = edge_tree.insert(tmpedg, edge_tree.root);
            }
            else
            {
                // if polygon is on the left side of the regular edge
                // then both the edges cannot be in the edge tree
                // hence we just update the helper of this vertex

                edge *leftedge = edge_tree.get_leftedge(&arr[i]);

                if (leftedge->helper->p->ptype == mergev)
                {

                    // we connect only if the helper vertex is merge vertex
                    // connect(leftedge->helper, arr[i]);
                    temp1[at] = arr[i].nd;
                    t[at][0] = arr[i].nd->p->index;
                    temp2[at] = leftedge->helper;
                    t[at][1] = leftedge->helper->p->index;
                    at++;
                }

                // updating the helper of left edge
                leftedge->helper = arr[i].nd;
            }
        }
        else if (arr[i].nd->p->ptype == splitv)
        {
            // treating split vertex
            // find the left edges which is visible from the split vertex
            // find the helper of this vertex and join this vertex with the split vertex
            // note that the helper always exists as as each edge is added with the
            edge *leftedge = edge_tree.get_leftedge(&arr[i]); // returns pointer to the node which has the helper vertex
            // connect(leftedge->helper->p, arr[i].nd->p);         // connects both the vertices
            temp1[at] = arr[i].nd;
            t[at][0] = arr[i].nd->p->index;
            temp2[at] = leftedge->helper;
            t[at][1] = leftedge->helper->p->index;
            at++;

            // update the helper as this edge
            leftedge->helper = arr[i].nd;

            // insert the newly discovered left edge in the tree with this vertex as helper
            edge tmpedg = edge(arr[i].nd, arr[i].nd->last, arr[i].nd);
            // insert the left adj edges in the tree
            edge_tree.root = edge_tree.insert(tmpedg, edge_tree.root);
        }
        else if (arr[i].nd->p->ptype == mergev)
        {
            // since the next vertex just after this is above it hence the edge connecting them is in the tree
            // hence we remove this edge from the tree and if its helper is a merge vertex we add a edge between them
            edge *topedge = edge_tree.get_topedge(&arr[i]); // returns pointer to the node which has the helper vertex

            edge tmpedge = edge(arr[i].next, arr[i].nd, nullptr);

            // this returns the edge in the tree which has bottom as this vertex
            // ##################### uncomment
            // edge* topedge  = edge_tree.get_topedge(&arr[i]);

            if (topedge->helper->p->ptype == mergev)
            {
                // we connect only if the helper vertex is merge vertex
                // connect(leftedge->helper, arr[i]);
                temp1[at] = arr[i].nd;
                t[at][0] = arr[i].nd->p->index;
                temp2[at] = topedge->helper;
                t[at][1] = topedge->helper->p->index;
                at++;
            }

            // delete the leftedge from the tree
            edge_tree.root = edge_tree.delete_node(edge_tree.root, *topedge);

            // get the new leftedge of this vertex
            edge *leftedge2 = edge_tree.get_leftedge(&arr[i]); // returns pointer to the node which has the helper vertex

            if (leftedge2->helper->p->ptype == mergev)
            {
                // we connect only if the helper vertex is merge vertex
                // connect(leftedge->helper, arr[i]);
                temp1[at] = arr[i].nd;
                t[at][0] = arr[i].nd->p->index;
                temp2[at] = leftedge2->helper;
                t[at][1] = leftedge2->helper->p->index;
                at++;
            }
            // update the helper as this edge
            leftedge2->helper = arr[i].nd;
        }
    }
}

void monotone_tringulate(polygon &p, int t[][2], int &at)
{
    if (p.n <= 3)
    {
        return;
    }
    int n = p.n;

    // copy and sort the polygon points
    onode *arr = new onode[n];

    node *start = p.points.head;
    int i = 0;
    do
    {
        arr[i].nd = start;
        arr[i].index = start->index;
        arr[i].next = start->next;
        arr[i].last = start->last;
        start = start->next;
        i++;
    } while (start != p.points.head);

    mergeSort_node(arr, 0, n - 1);

    stack s;
    s.push(arr[0].nd->p);
    s.push(arr[1].nd->p);
    // -1 for left 1 for right chain in the stack
    int chain;
    if (arr[0].nd->p->x >= arr[1].nd->p->x)
    {
        // left chain
        chain = -1;
    }
    else
    {
        // right chain
        chain = 1;
    }

    for (int i = 2; i < n; i++)
    {
        // need to implement adj and new span_interior_spl
        // if point is on the same side of reflex chain
        OK(i)
        if (arr[i].nd->p->adj(s.top->p))
        {
            // if adj to the points in stack

            // continue/ break if we reach to the end of the chain
            if (arr[i].nd->p->adj(s.top->next->p))
            {
                continue;
            }

            if (chain == -1)
            {
                // if stack has left chain
                if (s.top->p->span_interior(*(arr[i].nd->p), (*(s.top->next->p))) == -1)
                {
                    OK("spans")
                    // untill we reach the last vertex or we reach a vertex which is not visible
                    while ((s.size > 1) && (s.top->p->span_interior(*(arr[i].nd->p), (*(s.top->next->p))) == -1))
                    {
                        t[at][0] = arr[i].index;
                        t[at][1] = s.top->next->p->index;
                        at++;
                        s.pop();
                    }
                    s.push(arr[i].nd->p);
                }
                else
                {
                    s.push(arr[i].nd->p);
                }
            }
            else
            {
                // if stack has right chain
                if (s.top->p->span_interior((*(s.top->next->p)), *(arr[i].nd->p)) == -1)
                {
                    // untill we reach the last vertex or we reach a vertex which is not visible
                    while ((s.size > 1) && (s.top->p->span_interior((*(s.top->next->p)), *(arr[i].nd->p)) == -1))
                    {
                        t[at][0] = arr[i].index;
                        t[at][1] = s.top->next->p->index;
                        at++;
                        s.pop();
                    }
                    s.push(arr[i].nd->p);
                }
                else
                {
                    s.push(arr[i].nd->p);
                }
            }
        }
        else
        {

            container *ptr = s.top;
            point *temppt = ptr->p;
            while (ptr != s.bottom)
            {
                t[at][0] = arr[i].index;
                t[at][1] = ptr->p->index;
                at++;
                ptr = ptr->next;
                s.pop();
            }

            s.pop();
            s.push(temppt);
            s.push(arr[i].nd->p);
            chain *= (-1); // now the other side chain is in the stack hence change the sign
        }
    }
}

// function to split the polygons according to the diagonals
void split_polygon(polygon &p, polygon parr[], node *temp1[], node *temp2[], int n, int &pat, int &at)
{
    // divide into monotone polygons
    for (int j = 0; j < at; j++)
    {
        node *x = temp1[at];
        node *y = temp2[at];

        polygon p1, p2;
        p.split(y, x, p1, p2);
        parr[pat] = p2;
        pat++;
        p = p1;
    }

    if (at == 0)
    {
        parr[0] = p;
        pat++;
    }
}

// O(nlog(n)) time and O(n) space
void tringulate(polygon &p, int t[][2], int &at)
{
    if (p.n <= 3)
    {
        return;
    }
    int n = p.n;
    at = 0;
    node **temp1;
    node **temp2;
    temp1 = new node *[n];
    temp2 = new node *[n];

    // get the diagonal edges to add
    // temp1 and temp2 will store pointers to the nodes in the tree
    decompose_polygon(p, temp1, temp2, at, t);

    polygon *parr = new polygon[n];
    int pat = 0;
    split_polygon(p, parr, temp1, temp2, n, pat, at);

    // process each monotone polygon // works on strictly y monotone polygon
    for (int j = 0; j < pat; j++)
    {
        monotone_tringulate(parr[j], t, at);
    }

    return;
}

int main()
{

    // test_point();
    // return 0;
    XInitThreads();
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);
    // double a[][2] = {{0, 0}, {0.39, 0.5}, {0, 1}, {1, 1}, {0.4, 0.5}, {1, 0}};
    double a[100][2];
    int n;
    // freopen("output.txt", "w", stdin);
    // freopen("triang.txt", "w", stdout);
    cout << "Number of points: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i][0] >> a[i][1];
    }

    polygon p = polygon(n, a);

    p.show();

    // graphics for polygon
    double dx, dy, sx, sy;
    dx = 40.0;
    dy = -40.0;
    sx = 300.0;
    sy = 250.0;
    OK("try1")

    setcolor(GREEN);
    node *printer = p.points.head;
    do
    {
        line(dx * printer->p->x + sx, dy * printer->p->y + sy, dx * printer->next->p->x + sx, dy * printer->next->p->y + sy);
        printer = printer->next;
    } while (printer != p.points.head);
    // graphics for polygon

    OK("try2")

    int t[n - 3][2];

    int at = 0;
    tringulate(p, t, at);

    // p.show();
    setcolor(RED);
    for (int i = 0; i < at; i++)
    {
        cout << "(" << t[i][0] << "," << t[i][1] << ")" << endl;
        line(dx * a[t[i][0]][0] + sx, dy * a[t[i][0]][1] + sy, dx * a[t[i][1]][0] + sx, dy * a[t[i][1]][1] + sy);
    }

    getch();
    closegraph();
    return 0;
}

/*

int main()
{

    // points must be given in clockwise order from 0 to n-1
    double a[][2] = {{0, 0}, {0.39, 0.5}, {0, 1}, {1, 1}, {0.4, 0.5}, {1, 0}};
    int n=6;

    polygon p = polygon(n, a);

    int t[n - 3][2];
    int at = 0;

    tringulate(p, t, at);
    
    for (int i = 0; i < n - 3; i++)
    {
        cout << "(" << t[i][0] << "," << t[i][1] << ")" << endl;
    }

    return 0;
}

*/

/*

few test cases



*/