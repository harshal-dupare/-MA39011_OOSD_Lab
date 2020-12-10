#include <iostream>
using namespace std;

void addM(int a[3][3],int b[3][3],int ans[3][3])
{
	int n=3;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans[i][j]=a[i][j]+b[i][j];
		}
	}

}

void multM(int a[3][3],int b[3][3],int ans[3][3])
{
	int n=3;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
		    ans[i][j]=0;
			for(int k=0;k<n;k++)
			{
				ans[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	

}

void printM(int a[3][3])
{
    int n=3;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<a[i][j]<<" ";

		}
		cout<<endl;
	}

}

int main()
{
	int a[3][3]={{3,34,5533},{343,43,4},{3,23,8}};
	int b[3][3]={{1,2,3},{0,3,7},{4,2,8}};
	int ans[3][3]={{0,0,0},{0,0,0},{0,0,0}};
	int n=3;

	addM(a,b,ans);
	printM(ans);

	multM(a,b,ans);
	printM(ans);

	return 0;
}
