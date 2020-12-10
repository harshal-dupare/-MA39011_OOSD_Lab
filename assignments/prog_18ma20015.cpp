/*
Harshal Dupare | 18MA20015
20/11/20
*/

#include <iostream>
using namespace std;

#define ll long long

// in every problem we will be using bit representation to store a set
// for the coloring problem we will use base |colors| based number to represent the set ( which is natural extension of inclusion and exclusing set)

// function to get the number of 1 bits in binary representation of n
int get_bits(int n)
{
    int ct = 0;
    // loop until zero and return the 1 count and go to next bit each time
    while (n > 0)
    {
        if (n % 2 == 1)
            ct++;
        n /= 2;
    }
    return ct;
}

// get ith bit of n
int ibit(int n, int i)
{
    int c = n & (1 << i);
    if (c > 0)
    {
        return 1;
    }
    return 0;
}

// returns the max clique bit representation
int get_max_clique(int **a, int &mxsz, int n)
{
    // we itterate over all the possibility using number from 0 to 2^n-1
    int s = 0;
    int sz = 1 << n; // 2^n
    mxsz = 0;
    for (int i = sz - 1; i > 0; i--)
    {
        bool flg = true;
        int tsz = get_bits(i);
        // if total number of bits in more than the already known max clique only then we need to check
        if (tsz > mxsz)
        {
            // both store ith and jth index to check for if that has a edge
            int bi = 0, bj = 0;
            while (bi < n)
            {
                while (bj < n)
                {
                    if (ibit(i, bi) == 1 && ibit(i, bj) == 1)
                    {
                        if (a[bi][bj] == 0)
                        {
                            // if there is not a edge between any two vertex of the candidate set
                            // we just mark the flg flase as its not possible to be clique now
                            flg = false;
                        }
                    }
                    if (!flg)
                    {
                        break;
                    }
                    bj++;
                }
                // go to the next loop
                bj = 0;
                bi++;
                if (!flg)
                {
                    break;
                }
            }

            // if possible then update the set and size
            if (flg)
            {
                mxsz = tsz;
                s = i;
            }
        }
    }

    // return the bit representation if clique
    return s;
}

// checks if it is a vertex cover
bool is_vc(int e[][2], int s, int m)
{
    int p[m];
    // mark all not done
    for (int i = 0; i < m; i++)
    {
        p[i] = 0;
    }

    int xi = 0;
    while (s > 0)
    {
        if (s % 2 == 1)
        {
            for (int i = 0; i < m; i++)
            {
                // if not done
                if (p[i] == 0)
                {
                    // if this vertex covers it
                    if (e[i][1] == xi || e[i][0] == xi)
                    {
                        // mark it done
                        p[i] = 1;
                    }
                }
            }
        }
        xi++;
        s /= 2;
    }

    bool iss = true;
    for (int i = 0; i < m; i++)
    {
        if (p[i] == 0)
        {
            iss = false;
        }
    }

    return iss;
}

// gets the vertex cover as bit representation
int get_vertex_cover(int e[][2], int &mnsz, int n, int m)
{
    int s = 0;
    int sz = 1 << n;
    mnsz = n + 1;
    for (int i = 0; i < sz; i++)
    {
        bool flg = true;
        int tsz = get_bits(i);
        if (tsz < mnsz)
        {
            // if possible then compare it with min and update the minimum one
            bool poss = is_vc(e, i, m);
            if (poss)
            {
                mnsz = tsz;
                s = i;
            }
        }
    }

    return s;
}

// we will use long long to avoid overflow and to allow for graphs till size 15

// returns a^b
ll exp(ll a, ll b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    ll temp = exp(a, (b / 2));
    if (b % 2 == 0)
        return (temp * temp);

    temp = temp * temp;
    temp *= a;

    return temp;
}

// from a representation to colors
void rep_to_coloring(ll rep, ll b, ll colors[], int n)
{
    // repeat untill all the colors are assigned
    for (int i = 0; i < n; i++)
    {
        colors[i] = rep % b;
        rep /= b;
    }
}

// if it is valid colring or not
bool is_valid_color(int e[][2], ll coloring, ll base, int n, int m)
{
    ll colors[n];
    // get the coloring
    rep_to_coloring(coloring, base, colors, n);
    bool poss = true;
    for (int i = 0; i < m; i++)
    {
        // if any of the neighbours colors match then return false
        if (colors[e[i][1]] == colors[e[i][0]])
        {
            poss = false;
            break;
        }
    }
    // else true
    return poss;
}

// returns the size of the coloring
int get_coloring(int e[][2], int n, int m, ll fcoloring[])
{
    ll N = (ll)n; // converting to long long
    for (ll sz = 1; sz <= N; sz++)
    {
        ll total_case = exp(sz, n); // total cases to check for sz size colors
        for (ll i = 0; i < total_case; i++)
        {
            // if valid colring we just get the coloring and return
            bool poss = is_valid_color(e, i, sz, n, m);
            if (poss)
            {
                rep_to_coloring(i, sz, fcoloring, n);
                return sz;
            }
        }
    }

    // if everything fails then give all the vertices different colors
    for (int i = 0; i < n; i++)
    {
        fcoloring[i] = (ll)i;
    }
    return n;
}

int main()
{
    int edges[][2] = {{1, 2}, {1, 5}, {2, 5}, {2, 3}, {5, 4}, {4, 3}, {4, 6}};
    int n = 6;                                 // make sure to assign this properly
    int m = sizeof(edges) / (2 * sizeof(int)); // number of edges

    // set the matrix
    int **a;
    a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }

    // fill the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
    // fill as per the edges
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0] - 1, v = edges[i][1] - 1;
        a[u][v] = 1;
        a[v][u] = 1;
    }

    // output graph
    cout << "graph is :" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "{" << edges[i][0] << "," << edges[i][1] << "}, ";
    }
    cout << endl;
    cout << endl;

    // shifting edges to get zero based indexing
    for (int i = 0; i < m; i++)
    {
        edges[i][0]--;
        edges[i][1]--;
    }

    // max clique starts
    cout << "output of the max clique for the graph" << endl;
    int mxs;
    // making the diagonal entries 1 for considering 1 size clique
    for (int i = 0; i < n; i++)
        a[i][i] = 1;

    int s = get_max_clique(a, mxs, n);

    // making the diagonal entries 0 again
    for (int i = 0; i < n; i++)
        a[i][i] = 0;
    cout << "size of max clique is : " << mxs << endl;
    int ix = 1;
    cout << "max clique is : ";
    while (s > 0)
    {
        if (s % 2 == 1)
            cout << ix << ", ";
        s /= 2;
        ix++;
    }
    cout << endl;
    cout << endl;

    // max clique ends

    // vertex cover
    cout << "output of the vertex cover for the graph" << endl;
    int mns;
    int vs = get_vertex_cover(edges, mns, n, m);

    cout << "size is vertex color is  : " << mns << endl;
    ix = 1;
    cout << "vertex cover is : ";
    while (vs > 0)
    {
        if (vs % 2 == 1)
            cout << ix << ", ";
        vs /= 2;
        ix++;
    }
    cout << endl;
    cout << endl;

    // vertex cover ends

    // graph coloring
    cout << "output of the coloring for the graph" << endl;
    ll coloring[n];
    int sz = get_coloring(edges, n, m, coloring);

    cout << "size of coloring is : " << sz << endl;
    cout << "coloring is : ";
    for (int i = 0; i < n; i++)
    {
        cout << coloring[i] + 1 << ", ";
    }
    cout << endl;

    // graph coloring ends

    return 0;
}
