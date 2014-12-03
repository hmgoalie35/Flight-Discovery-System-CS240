#ifndef Date_H
#define Date_H
#include <string>
#include <iostream>
using namespace std;
class Date{
public:
    //default constructor
    Date();
    //constructor that takes in day, month, year
    Date(int, int, int);
    //prints a Date object in DD/MM/YYY format
    friend ostream& operator<<(ostream&, const Date&);
    //checks if 2 dates are equal
    bool operator==(const Date&);
    //checks if implicit param comes before date param.
    bool operator<(const Date&);
    //checks if implicit param comes after date param.
    bool operator>(const Date&);
private:
    //store the month, day, year.
    int month, day, year;
};
#endif