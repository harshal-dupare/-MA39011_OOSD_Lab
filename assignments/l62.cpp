#include <iostream>
#include <cmath>
#define PI 3.141592653

using namespace std;

// base class with virtual functions for area and perimeter
class Shape
{
public:
	virtual void area()
	{
		cout << "Base class area function\n";
	}
	virtual void perimeter()
	{
		cout << "Base class perimeter function\n";
	}
};

// Square shape class
class Square : public Shape
{
	// default is private
	// coordinates of all the points
	float dx1 = 0.0, dx2 = 1.0, dy1 = 0.0, dy2 = 1.0;

public:
	Square(float tx1, float ty1, float tx2, float ty2)
	{
		dx1 = tx1;
		dx2 = tx2;

		dy1 = ty1;
		dy2 = ty2;
	}
	void area()
	{
		// using s^2=a^2+b^2 theorem and get the area
		float a = (dx1 - dx2) * (dx1 - dx2) + (dy1 - dy2) * (dy1 - dy2);

		// printing the value
		cout << "Area of Square with points as:" << endl;
		cout << dx1 << ',' << dy1 << endl;
		cout << dx2 << ',' << dy2 << endl;
		cout << "Area: ";
		cout << a << endl;
	}

	void perimeter()
	{
		// just like in the above question we get the side of square and take its square root and multiply by 4
		float p = 4.0 * sqrt((dx1 - dx2) * (dx1 - dx2) + (dy1 - dy2) * (dy1 - dy2));

		// printing the value
		cout << "Perimeter of Square with points as:" << endl;
		cout << dx1 << ',' << dy1 << endl;
		cout << dx2 << ',' << dy2 << endl;
		cout << "Perimeter: ";
		cout << p << endl;
	}
};

// Triangle shape class
class Triangle : public Shape
{
	// default is private
	// coordinates of all the points
	float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;

public:
	Triangle(float tx1, float ty1, float tx2, float ty2, float tx3, float ty3)
	{
		x1 = tx1;
		x2 = tx2;
		x3 = tx3;

		y1 = ty1;
		y2 = ty2;
		y3 = ty3;
	}
	void area()
	{
		float s1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		float s2 = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
		float s3 = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
		float s = (s1 + s2 + s3) / 2.0;
		float a = sqrt(s * (s - s1) * (s - s2) * (s - s3));

		// printing the value
		cout << "Area of Triangle with points as:" << endl;
		cout << x1 << ',' << y1 << endl;
		cout << x2 << ',' << y2 << endl;
		cout << x3 << ',' << y3 << endl;
		cout << "Area: ";
		cout << a << endl;
	}

	void perimeter()
	{
		float s1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		float s2 = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
		float s3 = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
		float p = s1 + s2 + s3;

		// printing the value
		cout << "Perimeter of Triangle with points as:" << endl;
		cout << x1 << ',' << y1 << endl;
		cout << x2 << ',' << y2 << endl;
		cout << x3 << ',' << y3 << endl;
		cout << "Perimeter: ";
		cout << p << endl;
	}
};

// Circle shape class
class Circle : public Shape
{
	// default is private
	float cx = 0.0, cy = 0.0; // center x,y
	float r = 1.0;			  // radius length

public:
	Circle(float tx1, float ty1, float rr)
	{
		cx = tx1;
		cy = ty1;
		r = rr;
	}
	void area()
	{
		// using the formula and def of pi
		float a = PI * r * r;

		// printing the value
		cout << "Area of Circle with center as:" << endl;
		cout << cx << ',' << cy << endl;
		cout << "radius: " << endl;
		cout << r << endl;
		cout << "Area: ";
		cout << a << endl;
	}

	void perimeter()
	{
		// using the formula and def of pi
		float p = PI * 2 * r;

		// printing the value
		cout << "Perimeter of Circle with center as:" << endl;
		cout << cx << ',' << cy << endl;
		cout << "radius: " << endl;
		cout << r << endl;
		cout << "Perimeter: ";
		cout << p << endl;
	}
};

int main()
{
	// construct the shapes
	Circle c = Circle(0, 0, 12.3);
	Triangle t = Triangle(0, 0, 0.5, 2.3, 1.7, 1);
	Square s = Square(1.1, 1.2, 1.66, 5.3);

	// create the shape array of pointers
	Shape *ptr[3];
	ptr[0] = &c;
	ptr[1] = &t;
	ptr[2] = &s;

	// print the areas and perimeter
	for (int i = 0; i < 3; i++)
	{
		ptr[i]->area();
		ptr[i]->perimeter();
		cout << endl;
	}
	return 0;
}