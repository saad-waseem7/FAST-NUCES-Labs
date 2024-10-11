// The overall time complexity of the following C++ code is O(1), which means it operates in constant time. 

#include <iostream>
using namespace std;

class Account
{
private:
    int accountNumber;
    double balance;

public:
    Account(int accountNumber, double balance);
    ~Account();

    int get_accountNumber() const;
    void set_accountNumber(int accountNumber);

    double get_balance() const;
    void set_balance(double balance);

    void deposit(double amount);
    void withdraw(double amount);
    void display() const;
};

Account::Account(int accountNumber, double balance)
{
    this->accountNumber = accountNumber;
    this->balance = balance;
}

Account::~Account()
{
}

int Account::get_accountNumber() const
{
    return this->accountNumber;
}

void Account::set_accountNumber(int accountNumber)
{
    this->accountNumber = accountNumber;
}

double Account::get_balance() const
{
    return this->balance;
}

void Account::set_balance(double balance)
{
    this->balance = balance;
}

void Account::deposit(double amount)
{
    this->balance += amount;
}

void Account::withdraw(double amount)
{
    if (amount > this->balance)
    {
        cout << "Insufficient balance. Withdrawal amount exceeds current balance." << endl;
    }
    else
    {
        this->balance -= amount;
    }
}

void Account::display() const
{
    cout << "Account Number: " << this->accountNumber << endl;
    cout << "Balance: " << this->balance << endl;
}

int main()
{
    Account account(7690, 2000.0);
    account.display();
    account.deposit(600.0);
    account.display();
    account.withdraw(300.0);
    account.display();
    account.withdraw(2500.0);
    account.display();

    return 0;
}
