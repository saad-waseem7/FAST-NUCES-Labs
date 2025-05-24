#include <iostream>
#include <string>

using namespace std;

class BankAccount
{
public:
	BankAccount()
	{
		accountNumber = 0;
		accountHolderName = "";
		balance = 0.0;
	}

	BankAccount(int number, string name, double initialBalance)
	{
		accountNumber = number;
		accountHolderName = name;
		balance = initialBalance;
	}

	void deposit(double amount)
	{
		balance += amount;
	}

	void withdraw(double amount)
	{
		if (amount > balance)
		{
			cout << "Error: Insufficient balance. Unable to withdraw " << amount << "." << endl;
		}
		else
		{
			balance -= amount;
		}
	}

	void displayAccountInfo()
	{
		cout << "Account Number: " << accountNumber << endl;
		cout << "Account Holder Name: " << accountHolderName << endl;
		cout << "Current Balance: " << balance << endl;
	}

private:
	int accountNumber;
	string accountHolderName;
	double balance;
};

int main()
{
	BankAccount account1;
	account1.displayAccountInfo();
	cout << endl;

	int accNumber;
	string accName;
	double initial;

	cout << "Enter account number for account2: ";
	cin >> accNumber;
	cout << "Enter account holder name for account2: ";
        cin.ignore();
	getline(cin, accName);
	cout << "Enter initial balance for account2: ";
	cin >> initial;

	BankAccount account2(accNumber, accName, initial);

	double amount1, amount2;
	cout << "Enter amount to deposit: ";
	cin >> amount1;
	account2.deposit(amount1);

	cout << "Enter amount to withdraw: ";
	cin >> amount2;
	account2.withdraw(amount2);

	account2.displayAccountInfo();
	cout << endl;

	system("pause");
	return 0;
}