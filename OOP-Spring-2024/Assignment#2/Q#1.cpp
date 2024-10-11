#include <iostream>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);
    void Input();
    void Display_Date();
    void print();
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    int getDay();
    int getMonth();
    int getYear();
    int Compare(Date &d);
    Date IncrementMonth();
    ~Date();
};

Date::Date()
{
    day = 1;
    month = 1;
    year = 1926;
    cout << "Default Constructor Called" << endl;
}
Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
    cout << "Parameterized Constructor Called" << endl;
}
void Date::Input()
{
    cout << "Enter Day: ";
    cin >> day;
    while (day < 1 || day > 31)
    {
        cout << "Invalid day. Please enter a valid day: ";
        cin >> day;
    }

    cout << "Enter Month: ";
    cin >> month;
    while (month < 1 || month > 12)
    {
        cout << "Invalid month. Please enter a valid month: ";
        cin >> month;
    }
    cout << "Enter year: ";
    cin >> year;
    while (year < 0 || year > 9999)
    {
        cout << "Invalid year. Please enter a valid year: ";
        cin >> year;
    }
}

void Date::Display_Date()
{
    cout << "Date: " << day << "/" << month << "/" << year << endl;
}

void Date::print()
{
    cout << day << "/" << month << "/" << year << endl;
}

void Date::setDay(int day)
{
    this->day = day;
}

void Date::setMonth(int month)
{
    this->month = month;
}

void Date::setYear(int year)
{
    this->year = year;
}

int Date::getDay()
{
    return this->day;
}

int Date::getMonth()
{
    return this->month;
}

int Date::getYear()
{
    return this->year;
}

int Date::Compare(Date &d)
{
    if (year > d.year)
    {
        return 1;
    }
    else if (year < d.year)
    {
        return -1;
    }
    else
    {
        if (month > d.month)
        {
            return 1;
        }
        else if (month < d.month)
        {
            return -1;
        }
        else
        {
            if (day > d.day)
            {
                return 1;
            }
            else if (day < d.day)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }
}

Date Date::IncrementMonth()
{
    int newDay = this->day;
    int newMonth = this->month;
    int newYear = this->year;
    newMonth++;
    if (newMonth > 12)
    {
        newMonth = 1;
        newYear++;
    }
    return Date(newDay, newMonth, newYear);
}

Date::~Date()
{
    cout << "Destructor called" << endl;
}

int main()
{

    // Exercise#1
    cout << "\nExercise 1" << endl;
    Date date1(13, 3, 2024);
    date1.Display_Date();

    // Exercise#2
    cout << "\nExercise 2" << endl;
    // Default Constructor
    Date date2;
    date2.Display_Date();

    // Exercise#3
    cout << "\nExercise 3" << endl;
    // Print the date using print()
    cout << "Date1: ";
    date1.print();

    // Exercise#4
    cout << "\nExercise 4" << endl;
    // Created object of Date using overloaded/Parameterized constructor
    Date Day(14, 8, 2018);
    cout << "Independence Day: ";
    Day.print();

    // Exercise#5
    cout << "\nExercise 5" << endl;
    // Destructor make and call.

    // Exercise#6
    cout << "\nExercise 6" << endl;
    // Input from user using New Function
    Date date3;
    date3.Input();
    cout << "Date3: ";
    date3.print();

    // Exercise#7
    cout << "\nExercise 7" << endl;
    // Setters
    Date xmasDay1;
    cout << "Xmas Day: ";
    xmasDay1.print();
    cout << "Setting Xmas Day to 25/12/2018..." << endl;
    xmasDay1.setDay(25);
    xmasDay1.setMonth(12);
    xmasDay1.setYear(2018);
    cout << "Updated Xmas Day: ";
    xmasDay1.print();

    // Exercise#8
    cout << "\nExercise 8" << endl;
    // Getters
    Date xmasDay2;
    cout << "Xmas Day (Before setting using getters): ";
    cout << xmasDay2.getDay() << "/" << xmasDay2.getMonth() << "/" << xmasDay2.getYear() << endl;
    cout << "Setting Xmas Day to 25/12/2018..." << endl;
    xmasDay2.setDay(25);
    xmasDay2.setMonth(12);
    xmasDay2.setYear(2019);
    cout << "Updated Xmas Day (Using getters): ";
    cout << xmasDay2.getDay() << "/" << xmasDay2.getMonth() << "/" << xmasDay2.getYear() << endl;

    // Exercise#9
    cout << "\nExercise 9" << endl;
    // Compare
    Date date4(10, 3, 2024);
    Date date5(15, 3, 2024);

    int comparison = date4.Compare(date5);
    if (comparison == 1)
    {
        cout << "Date4 is greater than Date5" << endl;
    }
    else if (comparison == -1)
    {
        cout << "Date4 is smaller than Date5" << endl;
    }
    else
    {
        cout << "Date4 is equal to Date5" << endl;
    }

    // Exercise#10
    cout << "\nExercise 10" << endl;
    // Increment the month and print the new Date
    Date date6(2, 1, 2016);
    cout << "Original Date: ";
    date6.Display_Date();
    Date incrementedDate = date1.IncrementMonth();
    cout << "Date after Incrementing Month: ";
    incrementedDate.Display_Date();
    cout << endl;

    return 0;
}
