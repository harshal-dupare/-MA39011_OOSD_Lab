/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Class : 4
Date : 25-9-2020
Details: 2) As in the previous problem, write a function for multiplication. 

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

	// multiplies both the bnumbers as assigns to this number
	void mult_num(Number fint, Number sint)
	{

		// both the numbers as strings
		string s1 = fint.num;
		string s2 = sint.num;

		// we always choose the 2nd string to be the smallest
	    if(s1.length() > s2.length())swap(s1, s2); 
	  
	    int n1 = s1.length(), n2 = s2.length(); // ints to store the length of the strings

	  	// rversing the strings so that we can multiply from the last digits
	    reverse(s1); 
	    reverse(s2); 

	    // number to store the final answer
	    Number ans("0"); 

	    // loop over the number of digits of s1 to multiply s2 by each digit of s1 and then add it to a temp variable and repeat for other digits
	    for(int i=0; i<n1; i++) 
	    {
	    	string temp=""; // temporary string to store the answer
	    	for(int k=0; k<i; k++)
	    	{
	    		temp.push_back('0'); // adding the i number of zeros as nmultiplying by i'th digit so need to shift by that many zeros
	    	}

	    	// loop which goes through the digits of the 2nd number and multiplies them by the i'th digit of the 1st number and add assigns the result to the temp
	    	// if there is any carry we just take it to the next digit and add it
	    	int carry = 0; 
	    	for(int j=0; j<n2; j++)
	    	{
	    		int sum = (s1[i]-'0')*(s2[j]-'0')+carry; 
		        temp.push_back(sum%10 + '0'); 
		        carry = sum/10;
	    	}

	    	// if there are any carry to do we just add that the string
	    	if(carry)
		    {
		   	temp.push_back(carry+'0'); 
		    }

		    // reverse the number
	    	reverse(temp); 

	    	// adding the temp to the answer
	    	ans.add_num(ans,Number(temp));
	    }
	
	    num = ans.num;
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

	// multiplying n1 and n2 and storing to n3
	cout<<"Multiplication of the given numbers is:"<<endl;
	n3.mult_num(n1,n2);

	// showing n3
	n3.show_num();

	return 0;
} 



