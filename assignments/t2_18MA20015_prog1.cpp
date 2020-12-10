/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Class Test 2
Date : 21-10-2020\

1) Imagine a publishing company that markets both book and audiocassette versions of its works. 
Create a class publication that stores the title (a string) and price (type float ) of a publication.
 From this class derive two classes: book , which adds a page count (type int ), and tape , 
 which adds a playing time in minutes (type float ). Each of these three classes should have a getdata() function to
  get its data from the user at the keyboard, and a putdata() function to display its data. Write a main() program to test 
  the book and tape classes by creating instances of them, asking the user to fill in data with getdata() , and then displaying
   the data with putdata() . [5 marks]
*/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class publication
{

protected:
    string title;
    float price;

public:
    virtual void getdata() = 0;
    virtual void putdata() = 0;
};

class book : public publication
{
private:
    int pages;

public:
    void getdata()
    {
        cout << "Title of Book: ";
        // cin >> title;
        cin.ignore();
        getline(cin,title);
        cout << "Number of pages in the Book: ";
        cin >> pages;
        cout << "Price of Book: ";
        cin >> price;
        cout << endl;
    }

    void putdata()
    {
        cout << "Title: " << title << endl;
        cout << "Pages: " << pages << endl;
        cout << "Price: " << price << endl;
        cout << endl;
    }
};

class tape : public publication
{
private:
    float time;

public:
    void getdata()
    {
        cout << "Title: ";
        // cin >> title;
        cin.ignore();
        getline(cin,title);
        cout << "Price: ";
        cin >> price;
        cout << "Time: ";
        cin >> time;
        cout << endl;
    }

    void putdata()
    {
        cout << "Title : " << title << endl;
        cout << "Price : " << price << endl;
        cout << "Time : " << time << endl;
        cout << endl;
    }
};

int main()
{
    book bookvar;
    tape tapevar;

    cout << "| Book Details |" << endl;
    bookvar.getdata();
    cout << "| Tape Details |" << endl;
    tapevar.getdata();

    cout << "| This are the details of Book |" << endl;
    bookvar.putdata();
    cout << "| This are the details of Tape |" << endl;
    tapevar.putdata();

    return 0;
}