/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Date : 30-9-2020
Topic: Theory Test

*/

#include <iostream>

using namespace std;

void printArray(int p[], int n)
{
    for (int i = 0; i < n; i++)
        cout << p[i] << " ";
    cout << endl;
}

void partitions(int n)
{
    int p[n];
    int k = 0;
    p[k] = n;

    while (true)
    {

        printArray(p, k + 1);

        int rem_val = 0;
        while (k >= 0 && p[k] == 1)
        {
            rem_val += p[k];
            k--;
        }

        if (k < 0)
            return;

        p[k]--;
        rem_val++;

        while (rem_val > p[k])
        {
            p[k + 1] = p[k];
            rem_val = rem_val - p[k];
            k++;
        }

        p[k + 1] = rem_val;
        k++;
    }
}
int main()
{
    int x;
    cout << "Enter the number you want ordered partitions of : ";
    cin >> x;
    partitions(x);

    return 0;
}