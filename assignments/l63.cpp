#include <iostream>
#include <fstream>
using namespace std;

int main()
{

	freopen("input.txt", "r", stdin);	// redirects standard input to file
	freopen("output.txt", "w", stdout); // redirects standard output to file

	// reads character by character
	char s;
	while (cin >> s)
	{
		// if the char is an integer or '.' or ',' we write it to the output file else we dont
		// also note we write 1 ' ' after each ','
		int i = s - '0';
		if (i == -2 || i == -4 || (i >= 0 && i <= 9))
		{
			cout << s;
		}
		if (i == -4)
		{
			cout << ' ';
		}
	}

	return 0;
}