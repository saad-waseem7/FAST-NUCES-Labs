#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Car
{
protected:
    string model, transmission, engineChassisNumber;
    int manufactureYear, engineCapacity;
    double price;
    Car *next;

public:
    Car(string model, int year, double price, int engineCapacity, string transmission, string engineChassisNumber)
        : model(model), manufactureYear(year), price(price), engineCapacity(engineCapacity), transmission(transmission), engineChassisNumber(engineChassisNumber), next(nullptr) {}

    virtual double calculatePrice() { return price; }
    virtual void displayDetailsInTable(int index)
    {
        cout << "| " << setw(3) << index << " | " << setw(15) << model << " | " << setw(4) << manufactureYear
             << " | " << setw(10) << price << " | " << setw(6) << engineCapacity << " | " << setw(12) << transmission
             << " | " << setw(15) << engineChassisNumber << " |\n";
    }
    void setNext(Car *n) { next = n; }
    Car *getNext() { return next; }
    string getModel() { return model; }
};

class UsedCar : public Car
{
    string registrationNumber;

public:
    UsedCar(string model, int year, double price, int engineCapacity, string transmission, string engineChassisNumber, string registrationNumber)
        : Car(model, year, price, engineCapacity, transmission, engineChassisNumber), registrationNumber(registrationNumber) {}

    double calculatePrice() override
    {
        if (2024 - manufactureYear > 5)
            return price;    // No withholding tax
        return price * 1.15; // Adding 15% withholding tax
    }
};

class ImportedCar : public Car
{
    string auctionDate, auctionGrade;

public:
    ImportedCar(string model, int year, double price, int engineCapacity, string transmission, string engineChassisNumber, string auctionDate, string auctionGrade)
        : Car(model, year, price, engineCapacity, transmission, engineChassisNumber), auctionDate(auctionDate), auctionGrade(auctionGrade) {}
};

class Showroom
{
    Car *head;

public:
    Showroom() : head(nullptr) {}

    void addCar(Car *car)
    {
        if (!head)
        {
            head = car;
        }
        else
        {
            Car *temp = head;
            while (temp->getNext())
            {
                temp = temp->getNext();
            }
            temp->setNext(car);
        }
    }

    void displayCars()
    {
        cout << "\nAvailable Cars:\n";
        cout << "---------------------------------------------------------------------------------------\n";
        cout << "|  #  | Model           | Year | Price      | Engine | Transmission | Engine Chassis  |\n";
        cout << "---------------------------------------------------------------------------------------\n";
        Car *temp = head;
        int count = 1;
        while (temp)
        {
            temp->displayDetailsInTable(count++);
            temp = temp->getNext();
        }
        cout << "---------------------------------------------------------------------------------------\n";
    }

    void buyCar(int index)
    {
        if (!head)
        {
            cout << "No cars available!\n";
            return;
        }
        Car *temp = head;
        Car *prev = nullptr;
        int count = 1;
        while (temp && count < index)
        {
            prev = temp;
            temp = temp->getNext();
            count++;
        }
        if (!temp)
        {
            cout << "Invalid selection!\n";
            return;
        }

        string cnic, name, employeeId;
        cout << "Enter your CNIC: ";
        cin >> cnic;
        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your Employee ID: ";
        cin >> employeeId;

        cout << "You have successfully purchased " << temp->getModel() << "!\n";
        cout << "Customer Details:\n";
        cout << "CNIC: " << cnic << "\n";
        cout << "Name: " << name << "\n";
        cout << "Employee ID: " << employeeId << "\n";

        if (prev)
            prev->setNext(temp->getNext());
        else
            head = temp->getNext();
        delete temp;
    }
};

int main()
{
    Showroom showroom;
    showroom.addCar(new UsedCar("Toyota Corolla", 2018, 15000, 1600, "Automatic", "EN1234", "ABC-123"));
    showroom.addCar(new ImportedCar("BMW X5", 2022, 50000, 3000, "Automatic", "EN5678", "2023-05-10", "Grade A"));
    showroom.addCar(new UsedCar("Honda Civic", 2017, 14000, 1800, "Manual", "EN9101", "XYZ-789"));
    showroom.addCar(new ImportedCar("Ferrari F-40", 2023, 60000, 2500, "Automatic", "EN2468", "2023-06-15", "Grade S"));
    showroom.addCar(new UsedCar("Ford Mustang", 2015, 30000, 5000, "Manual", "EN1357", "MUS-555"));

    int choice;
    while (true)
    {
        cout << "\n1. Display Available Cars\n2. Buy a Car\n3. Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            showroom.displayCars();
        }
        else if (choice == 2)
        {
            int carIndex;
            cout << "Enter the number of the car you want to buy: ";
            cin >> carIndex;
            showroom.buyCar(carIndex);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
