#include <iostream>
#include <string>

using namespace std;

class Employee
{
protected:
    string name;
    int id;

public:
    Employee();
    Employee(string name, int id);
    void displayDetails();
    ~Employee();
};

class Manager : public Employee
{
private:
    string department;

public:
    Manager();
    Manager(string name, int id, string department);

    void displayDetails();
    ~Manager();
};

class Developer : public Employee
{
private:
    string programmingLanguage;

public:
    Developer();
    Developer(string name, int id, string programmingLanguage);
    void displayDetails();
    ~Developer();
};

//
Employee::Employee() : name(""), id(0) {}

Employee::Employee(string name, int id) : name(name), id(id) {}

void Employee::displayDetails()
{
    cout << "Name: " << name << endl;
    cout << "Employee ID: " << id << endl;
}
Employee::~Employee()
{
    // cout << "Employee object destroyed" << endl;
}

//

Manager::Manager() : department("") {}

Manager::Manager(string name, int id, string department) : Employee(name, id), department(department) {}

void Manager::displayDetails()
{
    Employee::displayDetails();
    cout << "Department: " << department << endl;
}

Manager::~Manager()
{
    // cout << "Manager object destroyed" << endl;
}

//

Developer::Developer() : programmingLanguage("") {}

Developer::Developer(string name, int id, string programmingLanguage) : Employee(name, id), programmingLanguage(programmingLanguage) {}

void Developer::displayDetails()
{
    Employee::displayDetails();
    cout << "Programming Language: " << programmingLanguage << endl;
}

Developer::~Developer()
{
    // cout << "Developer object destroyed" << endl;
}

int main()
{
    string name, department, programmingLanguage;
    int id;

    cout << "Enter Manager details:" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Department: ";
    getline(cin, department);

    Manager manager(name, id, department);

    cout << "\nEnter Developer details:" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Programming Language: ";
    getline(cin, programmingLanguage);

    Developer developer(name, id, programmingLanguage);

    // Displaying details of employees
    cout << "\nManager Details:" << endl;
    manager.displayDetails();
    cout << "\nDeveloper Details:" << endl;
    developer.displayDetails();

    return 0;
}