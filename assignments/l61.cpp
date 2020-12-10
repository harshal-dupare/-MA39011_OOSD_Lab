#include <iostream>
using namespace std;

// English Distance Class
struct Distance
{
public:
	int thou = 0;
	int inch = 0;
	int foot = 0;
	int yard = 0;
	int chain = 0;
	int furlong = 0;
	int mile = 0;
	int league = 0;

	// simplify the values by reducing from the smallest unit and carry it forward to the larger unit
	// just like we do decimal addition
	void simplify()
	{
		if (thou >= 1000)
		{
			inch += (thou / 1000);
			thou %= 1000;
		}

		if (inch >= 12)
		{
			foot += (inch / 12);
			inch %= 12;
		}

		if (foot >= 3)
		{
			yard += (foot / 3);
			foot %= 3;
		}

		if (yard >= 22)
		{
			chain += (yard / 22);
			yard %= 22;
		}

		if (chain >= 10)
		{
			furlong += (chain / 10);
			chain %= 10;
		}

		if (furlong >= 8)
		{
			mile += (furlong / 8);
			furlong %= 8;
		}

		if (mile >= 3)
		{
			league += (mile / 3);
			mile %= 3;
		}
	}
};

int main()
{

	while (true)
	{
		// ask for input
		cout << "Do you wanna try one more conversion? (Y/N) :  ";
		char c;
		cin >> c;
		if (c == 'Y')
		{
			// get the values
			Distance d = Distance();
			cout << "input the thou: ";
			cin >> d.thou;
			cout << "input the inch: ";
			cin >> d.inch;
			cout << "input the foot: ";
			cin >> d.foot;
			cout << "input the yard: ";
			cin >> d.yard;
			cout << "input the chain: ";
			cin >> d.chain;
			cout << "input the furlong: ";
			cin >> d.furlong;
			cout << "input the mile: ";
			cin >> d.mile;
			cout << "input the league: ";
			cin >> d.league;

			// simplify it and print
			d.simplify();
			cout << "Simplified conversion is \n";
			cout << "thou: " << d.thou << ", ";
			cout << "inch: " << d.inch << ", ";
			cout << "foot: " << d.foot << ", ";
			cout << "yard: " << d.yard << ", ";
			cout << "chain: " << d.chain << ", ";
			cout << "furlong: " << d.furlong << ", ";
			cout << "mile: " << d.mile << ", ";
			cout << "league: " << d.league << endl;
			cout << endl;
		}
		else if (c == 'N')
		{
			break;
		}
		else
		{
			cout << "Give proper input!\n";
		}
	}

	return 0;
}