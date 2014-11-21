#include "Date.h"

/**
 * default constructor
 */
Date::Date(){
    month = day = year = 0;
}

/**
 * value constructor, takes day, month and year as params
 */
Date::Date(int the_day, int the_month, int the_year){
    month = the_month;
    day = the_day;
    year = the_year;
}

/**
 * print to cout
 */
ostream& operator<<(ostream& out, const Date& date){
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}

/**
 * equals operator, if the day month and year match then the dates are equal
 */
bool Date::operator==(const Date& date){
    return (day == date.day && month == date.month && year == date.year);
}

/**
 * check if implicit param comes before date.
 */
bool Date::operator<(const Date& date){
    bool ret_val = false;
    if(year == date.year){
        if(month == date.month){
            if(day == date.day){
                ret_val = false;
            }else if(day < date.day){
                ret_val = true;
            }
        }else if(month < date.month){
            ret_val = true;
        }
    }else if(year < date.year){
        ret_val = true;
    }
    return ret_val;
}

/**
 * check if implicit param comes before date
 */
bool Date::operator>(const Date& date){
    bool ret_val = false;
    if(year == date.year){
        if(month == date.month){
            if(day == date.day){
                ret_val = false;
            }else if(day > date.day){
                ret_val = true;
            }
        }else if(month > date.month){
            ret_val = true;
        }
    }else if(year > date.year){
        ret_val = true;
    }
    return ret_val;
}