#include <iostream>
using namespace std;

int* multM(int a[][],int b[][])
{
	int ans[][]={{0,0,0},{0,0,0},{0,0,0}}
	int n=3;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans[i][j]=a[i][j]+b[i][j];
		}
	}

return ans
}

void addM(int a[][],int b[][])
{
	
}

int maxidx(int a[],int n)
{
    int mxidx=0;
	for(int j=0;j<n;j++)
	{
		if(a[mxidx]<a[j])
		{
			mxidx=j;
		}
	}
	return mxidx;
}

void sortsq(int a[])
{
	int n=sizeof(a)/sizeof(int);
	for(int i=n-1;i>-1;i--)
	{
		int mxidx=0;
		for(int j=0;j<i;j++)
		{
			if(a[mxidx]<a[j])
			{
				mxidx=j;
			}
		}
		int temp=a[i];
		a[i]=a[mxidx];
		a[mxidx]=temp;
	}
}


int main()
{
	int a[]={3,34,5533,343,43,4,3,23};
	int n=sizeof(a)/sizeof(int);
	/*
	int mx=a[0];
	for(int i=1;i<n;i++)
	{
		if(a[i]>mx)
		{
			mx=a[i];
		}
	}
	cout<<mx<<endl;
	*/

	for(int i=n-1;i>-1;i--)
	{
		int mxidx=0;
		for(int j=0;j<i;j++)
		{
			if(a[mxidx]<a[j])
			{
				mxidx=j;
			}
		}
		int temp=a[i];
		a[i]=a[mxidx];
		a[mxidx]=temp;
	}

	return 0;
}
