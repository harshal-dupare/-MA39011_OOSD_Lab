/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Class : 4
Date : 25-9-2020
Details:
We want to implement precision mathematics. For this, write a class Number,
which takes as input an arbitrarily large integer as a string of numbers via a member function get_num,
and may display it via a member function show_num. It also has a member function add for adding such two numbers.
The name of this program should be prog1.cpp
*/

#include <iostream>
#include <string.h>

using namespace std;

// function to reverse the string
void reverse(string& str) 
{ 
    int n = str.length(); 
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 
} 


class Number
{
private:
	string num; // string to store the number

public:

	Number (string s)
	{
		num = s; // assign the number as string
	}

	// gets the number as string and assigns to the num
	void get_num(string sint)
	{
		num = sint;
	}

	// prints the number
	void show_num()
	{
		cout<<num<<endl;
	}

	// adds the numbers and assigns to this number
	void add_num(Number fint, Number sint)
	{

		string s1 = fint.num;
		string s2 = sint.num;

		// we always choose the 2nd string to be the smallest
	    if(s1.length() > s2.length())swap(s1, s2); 
	  
	    int n1 = s1.length(), n2 = s2.length(); // ints to store the length of the strings

	  	// rversing the strings so that we can add from the last digit 
	    reverse(s1); 
	    reverse(s2); 

	    string ans = "";  // string to store the answer
	    // main loop which goes through each last pair of digits and add them to the answer till the max digit of the smallest number
	    // if there is any carry we just take it to the next digit and add it
	    int carry = 0; 
	    for(int i=0; i<n1; i++) 
	    { 
	        int sum = (s1[i]-'0')+(s2[i]-'0')+carry; 
	        ans.push_back(sum%10 + '0'); 
	        carry = sum/10; 
	    }

	    // since both numbers can be on different length we need to just take the digits of the larger number 
	    // and if there is any carry just add it one by one and get the most significant digits of the number
	    for(int i=n1; i<n2; i++) 
	    { 
	        int sum = (s2[i]-'0')+carry; 
	        ans.push_back(sum%10 + '0'); 
	        carry = sum/10; 
	    }

	    // if there are any carry to do we just add that the string
	    if(carry)
	    {
	   	ans.push_back(carry+'0'); 
	    }

	    // reverse the number
	    reverse(ans); 

	    // assign the answer to the num
	    num = ans;
	}
};

int main()
{
	// constructing 2 numbers by taking input from user
	string s;

	cout<<"Give the First Number: ";
	cin>>s;
	Number n1(s);
	cout<<"Give the Second Number: ";
	cin>>s;
	Number n2(s);

	// 3rd Number using get_num methods
	Number n3("");
	n3.get_num("3141");

	// showing the numbers
	cout<<"Showing first number using show num method: ";
	n1.show_num();

	cout<<"Showing Second number using show num method: ";
	n2.show_num();

	// adding n1 and n2 and storing int n3
	n3.add_num(n1,n2);
	cout<<"Addition of the given numbers is: "<<endl;
	// showing n3
	n3.show_num();

	return 0;
} 

