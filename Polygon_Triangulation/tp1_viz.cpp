/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Date : 8-11-2020
Time complexity : O(n^2)
Space complexity : O(n)
Method : Ear clipping method
*/

#include <iostream>
#include <graphics.h>
#include <X11/Xlib.h>
#define EPS 1e-8

using namespace std;

#define OK(x) cout << #x << " : " << x << " " << endl;

// class to store the point and related methods
class point
{
public:
    // values to store x and y coordinates of point
    double x;
    double y;
    // default constructor
    point()
    {
        x = 0;
        y = 0;
    }
    // constructor with x and y value
    point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    // function to set x and y value
    void set(double x, double y)
    {
        this->x = x;
        this->y = y;
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
    // returns 1 if in the segment , 0 if on the line contaning the segment, else -1
    int in_segment(point &p1, point &p2)
    {
        // delta is distance from the line
        double delta = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);

        // not on line
        if (abs(delta) > EPS)
        {
            return -1;
        }

        // if on line then need to check if inside the segment
        // int values to store the sign of axial distances from both the points p1 and p2
        int sign_p1x, sign_p2y, sign_p2x, sign_p1y;
        double temp;
        temp = this->x - p1.x;

        // simple cases to check the sign to the precision of EPS
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

        // int value to store on which side the points is
        int side;

        // if line is not vertical
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
            // if line is vertical then check y axis distance signs
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
            // degenerate case where both points of line are very close
            // to not be considered as distinct points to the precision of the EPS value
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

        // simple cases to check the sign
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

        // if any of points on line then return 0 else if both have same distance sign return 1 else -1
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
        // int values to store the cases of points if they lie on same side of lines
        int abc, bca, cab;
        abc = this->on_same_side(a, b, c);
        bca = this->on_same_side(b, c, a);
        cab = this->on_same_side(c, a, b);

        // int values to store if this point lies in the segments or not
        int sign_bc = this->in_segment(b, c);
        int sign_ca = this->in_segment(c, a);
        int sign_ab = this->in_segment(a, b);

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

    // utility function to print the point
    void show()
    {
        cout << "(" << x << "," << y << ") ";
        return;
    }
};

// class to store the node for the linked list structure
class node
{
public:
    point p;              // point data
    int index;            // index of that point
    node *next = nullptr; // pointer to the next node
    node *last = nullptr; // pointer to the last node

    // constructor which takes input as index
    node(int index)
    {
        this->index = index;
        p = point();
    }
};

// circular linked list structure
class circular_linked_list
{
public:
    node *head; // head of the linked list
    int n;      // number of nodes in the linked list
    // default constructor
    circular_linked_list()
    {
        this->head = nullptr;
        this->n = 0;
    }
    // O(n) time
    // constructor which creates the linked list fromthe points in ps[][2];
    circular_linked_list(int n, double ps[][2])
    {
        // if no points then return by making head null and n = 0
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
        head->p = point(ps[i][0], ps[i][1]);
        node *temp = head;
        i++;
        while (i < n)
        {
            temp->next = new node(i);                  //next pointer
            temp->next->p = point(ps[i][0], ps[i][1]); // next node data is filled
            temp->next->last = temp;                   // last of the next must point to temp node itself( i.e. the node we are on)
            temp = temp->next;                         // going to the next node created just now
            i++;
        }
        temp->next = head; // at the end the last node must point to head
        head->last = temp; // and head must point the the last node using last pointer
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
        newx->p = point(x->p.x, x->p.y);

        node *newy = new node(y->index);
        // connecting the new x node to the the next of y
        newy->next = y->next;
        y->next->last = newy;
        newy->p = point(y->p.x, y->p.y);

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

        // if head is null then return 0
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
            temp->p.show();
            temp = temp->next;
        } while (temp != this->head);

        return;
    }
};

// class to store a polygon using circular linked list
class polygon
{
public:
    int n;                       // size of polygon
    circular_linked_list points; // list to store the points

    // default constructor
    polygon()
    {
        this->n = 0;
    }
    // method to set the polygon
    void set(int n, double ps[][2])
    {
        points = circular_linked_list(n, ps);
        this->n = n;
    }

    // constructor with size and points as input
    polygon(int n, double ps[][2])
    {
        points = circular_linked_list(n, ps);
        this->n = n;
    }

    // split the polygon into 2 polygons across x and y and allocate them to p1 and p2
    void split(node *x, node *y, polygon &p1, polygon &p2)
    {
        points.split(x, y, p1.points, p2.points); // splits the polygon
        p1.n = p1.points.n;                       // assigns the size of list to the polygon 1
        p2.n = p2.points.n;                       // assigns the size of list to the polygon 2
    }

    // utility function to print the polygon
    void show()
    {
        points.print();
        cout << endl;
    }
};

// O(1) time
// as span_interior returns -1 if clockwise 1 if anticlockwise for internal angle else it returns 1,-1 respectively
// clockwise/anticlockwise wrt the order last->head->next
// in our case as input is clockwise we expect -1 as output for internal angles
int span_interior(node *next, node *head, node *last)
{
    // get the vectors v1 and v2 x and y values
    double v1x = head->p.x - last->p.x;
    double v1y = head->p.y - last->p.y;
    double v2x = next->p.x - head->p.x;
    double v2y = next->p.y - head->p.y;

    // compute the cross product which has factor of sine of angle between them
    // hence checking the sign of it we can tell if its internal or external angle
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

// O(n^2) time and O(n) space
// each call has complexity of O(n) time and O(1) space
// after each call 1 triangulation diagoal is added
// as there at n-2 such diagonals we have time complexity of O(n^2) and space complexity of O(n)
void tringulate(polygon &p, int t[][2], int &at)
{
    // if polygon is triangle or has less than 3 points (degenerate case) simply return
    if (p.n <= 3)
    {
        return;
    }

    int n = p.n;
    node *head = p.points.head; // get the starting point to consider for clipping the ear as head of the points list
    node *last = head->last;    // get the last vertex wrt the head
    node *next = head->next;    // get the next vertex wrt the head

    // loop until we find a point which has internal angle in the polygon
    // as span_interior returns -1 if clockwise 1 if anticlockwise for internal angle else it returns 1,-1 respectively
    while (span_interior(next, head, last) != -1)
    {
        head = head->next;
        last = last->next;
        next = next->next;
    }

    // once we find such internal angle points they form a ear
    point &a = head->p;
    point &b = next->p;
    point &c = last->p;

    // we check if the ear is valid or not
    // if not then we add the diagonal with the center of ear and the point furthest from the line (last----next) which is within the ear
    node *maxdist_pt = nullptr; // pointer to store that max distance point
    double maxdist = -1.0;      // the maximum distance
    node *temp = next->next;    // temporary node itterate over the polygon
    while (temp != last)
    {
        // if temp point is in the triangle
        if (temp->p.in_triangle(a, b, c) != -1)
        {
            // we check the distance
            double dist = temp->p.dist_line(b, c);
            if (dist >= maxdist)
            {
                // if distance is more than the last distance we change the point
                maxdist = dist;
                maxdist_pt = temp;
            }
        }
        temp = temp->next; // check the next point
    }

    if (maxdist_pt != nullptr)
    {
        // if there was a point in the ear we join it to that as split the polygon about that diagonal
        t[at][0] = head->index;       // 1st point of the diagonal
        t[at][1] = maxdist_pt->index; // 2nd point of the diagonal
        at++;
        polygon p1, p2;
        p.split(head, maxdist_pt, p1, p2);

        tringulate(p1, t, at); // now we solve the smaller problem on p1
        tringulate(p2, t, at); // now we solve the smaller problem on p2
        return;
    }
    else
    {
        // if there wasnt any point then we simply clip the ear and split about the ear
        t[at][0] = last->index;
        t[at][1] = next->index;
        at++;
        polygon p1, p2;
        p.split(last, next, p1, p2);

        tringulate(p1, t, at); // now we solve the smaller problem on p1
        tringulate(p2, t, at); // now we solve the smaller problem on p2
        return;
    }

    return;
}

int rd(double a, double b)
{
    double random = ((double)rand()) / (double)RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return (int)(a + r);
}

void test_point()
{
    int n = 50;
    double mn = -50.0, mx = 50.0;
    while (n--)
    {
        // point a(rd(mn, mx), rd(mn, mx));
        // point b(rd(mn, mx), rd(mn, mx));
        // point c(rd(mn, mx), rd(mn, mx));
        // point d(rd(mn, mx), rd(mn, mx));
        point a(0, 0);
        point b(10, 0);
        point c(0, 10);
        point d(rd(mn, mx), rd(mn, mx));
        if (n == 49)
        {
            d.x = 5;
            d.y = 5;
        }
        // OK(a.x)
        // OK(a.y)
        // OK(b.x)
        // OK(b.y)
        // OK(c.x)
        // OK(c.y)
        OK(d.x)
        OK(d.y)
        OK(d.on_same_side(a, b, c))
        OK(d.in_segment(b, c))
        OK(d.in_triangle(a, b, c))
        cout << endl;
    }

    cout << endl;
}

int main()
{

    // test_point();
    // return 0;
    XInitThreads();
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);
    // points must be given in clockwise order from 0 to n-1
    // double a[][2] = {{0, 0}, {0.39, 0.5}, {0, 1}, {1, 1}, {0.4, 0.5}, {1, 0}};
    double a[100][2];
    int n;
    // freopen("output.txt", "w", stdin);
    // freopen("triang.txt", "w", stdout);
    cout << "Enter the polygon points in clockwise order\n";
    cout << "Number of points: \n";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i][0] >> a[i][1];
    }

    polygon p = polygon(n, a);

    p.show();

    // graphics for polygon
    double dx, dy, sx, sy;
    dx = 30.0;
    dy = 30.0;
    sx = 200.0;
    sy = 200.0;

    setcolor(GREEN);
    node *printer = p.points.head;
    do
    {
        line(dx * printer->p.x + sx, dy * printer->p.y + sy, dx * printer->next->p.x + sx, dy * printer->next->p.y + sy);
        printer = printer->next;
    } while (printer != p.points.head);
    // graphics for polygon

    int t[n - 3][2];
    int at = 0;

    tringulate(p, t, at);
    setcolor(RED);
    for (int i = 0; i < n - 3; i++)
    {
        cout << "(" << t[i][0] << "," << t[i][1] << ")" << endl;
        line(dx * a[t[i][0]][0] + sx, dy * a[t[i][0]][1] + sy, dx * a[t[i][1]][0] + sx, dy * a[t[i][1]][1] + sy);
    }

    getch();
    closegraph();
    return 0;
}


/*

commands
* launch Xming server
$  export DISPLAY=:0
$ g++
$ g++ -o test.exe tp1_viz.cpp -lX11 -lgraph
$ ./test.exe

*/