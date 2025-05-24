#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
private:
    string name;
    int year;

public:
    Vehicle();
    Vehicle(string name, int year);
    void setName(string name);
    void setYear(int year);
    string getName();
    int getYear();
    void print() const;
    ~Vehicle();
};

Vehicle::Vehicle()
{
    this->name = "";
    this->year = 0;
}

Vehicle::Vehicle(string name, int year)
{
    this->name = name;
    this->year = year;
}

void Vehicle::setName(string name)
{
    this->name = name;
}

void Vehicle::setYear(int year)
{
    this->year = year;
}

string Vehicle::getName()
{
    return this->name;
}

int Vehicle::getYear()
{
    return this->year;
}

void Vehicle::print() const
{
    cout << "Name: " << this->name << endl;
    cout << "Year: " << this->year << endl;
}

Vehicle::~Vehicle()
{
    // cout << "Destructor called" << endl;
}

class Car : public Vehicle
{
private:
    int numDoors;

public:
    Car();
    Car(string make, int year, int numDoors);
    void setNumDoors(int numDoors);
    int getNumDoors() const;
    void print() const;
    ~Car();
};

Car::Car() : Vehicle(), numDoors(0) {}

Car::Car(string make, int year, int numDoors) : Vehicle(make, year), numDoors(numDoors) {}

void Car::setNumDoors(int numDoors)
{
    this->numDoors = numDoors;
}

int Car::getNumDoors() const
{
    return numDoors;
}

void Car::print() const
{
    Vehicle::print();
    cout << "Number of doors: " << numDoors << endl;
}

Car::~Car()
{
    // cout << "Destructor called" << endl;
}

class Bike : public Vehicle
{
private:
    int engineSize;

public:
    Bike();
    Bike(string make, int year, int engineSize);
    void setEngineSize(int engineSize);
    int getEngineSize() const;
    void print() const;
    ~Bike();
};

Bike::Bike() : Vehicle(), engineSize(0) {}

Bike::Bike(string make, int year, int engineSize) : Vehicle(make, year), engineSize(engineSize) {}

void Bike::setEngineSize(int engineSize)
{
    this->engineSize = engineSize;
}

int Bike::getEngineSize() const
{
    return engineSize;
}

void Bike::print() const
{
    Vehicle::print();
    cout << "Engine size: " << engineSize << " cc" << endl;
}

Bike::~Bike()
{
    // cout << "Destructor called" << endl;
}

int main()
{
    string make;
    int year, numDoors, engineSize;

    cout << "Enter car details:" << endl;
    cout << "Make: ";
    getline(cin, make);
    cout << "Year: ";
    cin >> year;
    cout << "Number of doors: ";
    cin >> numDoors;

    Car myCar(make, year, numDoors);

    cin.ignore();

    cout << endl;
    cout << "Enter bike details:" << endl;
    cout << "Make: ";
    getline(cin, make);
    cout << "Year: ";
    cin >> year;
    cout << "Engine size (cc): ";
    cin >> engineSize;

    Bike myBike(make, year, engineSize);

    cout << endl;
    cout << "Car details:" << endl;
    myCar.print();
    cout << endl;

    cout << "Bike details:" << endl;
    myBike.print();
    cout << endl;

    return 0;
}