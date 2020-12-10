/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Date : 30-9-2020
Topic: Theory Test
Details:
*/

#include <iostream>

using namespace std;

int cond(int n,int* a)
{
	int i=0;
	while(n>0)
	{
		a[i]=n%7;
		i++;
		n=n/10;
	}

	return i;
}

int cnum(int* a, int n)
{
	int ans=0;
	for(int i=0;i<n;i++)
	{
		ans=ans*10+a[i];
	}

	return ans;
}

int add_num(int n, int m)
{

	int emp=m;
  	if(n<m){m=n;n=emp;}
    int n1 ,n2;
    int s1[100],s2[100];
    n1=cond(n,s1);
    n2=cond(m,s2);


    int ans[100];  // string to store the answer
    // main loop which goes through each last pair of digits and add them to the answer till the max digit of the smallest number
    // if there is any carry we just take it to the next digit and add it
    int carry = 0; 
    int dg=0;
    for(int i=0; i<n1; i++) 
    { 
        int sum = (s1[i])+(s2[i])+carry; 
        ans[i]=(sum%7); 
        carry = sum/7; 
       	dg++;
    }

    // since both numbers can be on different length we need to just take the digits of the larger number 
    // and if there is any carry just add it one by one and get the most significant digits of the number
    for(int i=n1; i<n2; i++) 
    { 
        int sum = (s2[i])+carry; 
        ans[i]=(sum%7); 
        carry = sum/7; 
        dg++;
    }

    // if there are any carry to do we just add that the string
    if(carry)
    {
   	ans[n2]=(carry); 
   	dg++;
    }
    // assign the answer to the num
    return cnum(ans,dg);
}

// multiplies both the bnumbers as assigns to this number
int mult_num(int n, int m)
{

	int emp=m;
    if(n<m){m=n;n=emp;}
    int n1 ,n2;
    int s1[100],s2[100];
    n1=cond(n,s1);
    n2=cond(m,s2);

    int ans[100];

    // loop over the number of digits of s1 to multiply s2 by each digit of s1 and then add it to a temp variable and repeat for other digits
    for(int i=0; i<n1; i++) 
    {
    	int temp[100]; // temporary string to store the answer
    	for(int k=0; k<i; k++)
    	{
    		temp[k]=0; // adding the i number of zeros as nmultiplying by i'th digit so need to shift by that many zeros
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

int main()
{

	int n;
	cout<<"enter the 1st number:";
	cin>>n;
	int m;
	cout<<"enter the 2nd number:";
	cin>>m;

	int k=add_num(n,m);



	return 0;
}