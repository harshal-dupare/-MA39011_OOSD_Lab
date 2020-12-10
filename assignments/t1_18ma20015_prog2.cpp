/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Date : 30-9-2020
Topic: Theory Test
Details:
*/

#include <iostream>

using namespace std;


double cbroot(double n) 
{ 
    double xl = n;
  
    double EPS = 1e-8; 
  
    double del = 10.0;
  
    double x; 
 
    while (del> EPS) 
    { 

        x = ((2.0) * xl + (double)n/(xl*xl)) /3.0; 
        del = abs(x - xl); 
        xl = x; 
    } 
  
    return x;
}

int main()
{
    double x;
    cout<<"Enter the number you want cube root of : ";
    cin>>x;
    double ans=cbroot(x);
    cout<<"Cube root is: "<<ans<<endl;

	return 0;
}