-- Create database Schema
USE master;
GO
CREATE DATABASE Branch;
GO
USE Branch

-- Create Customers Table
CREATE TABLE Customers (
    CustomerID INT PRIMARY KEY,
    FirstName NVARCHAR(50),
    LastName NVARCHAR(50),
    DateOfBirth DATE,
    Address NVARCHAR(255),
    PhoneNumber NVARCHAR(15),
    Email NVARCHAR(100),
    RegistrationDate DATE
);

-- Insert Sample Data into Customers
INSERT INTO Customers (CustomerID, FirstName, LastName, DateOfBirth, Address, PhoneNumber, Email, RegistrationDate) VALUES
(1, 'John', 'Doe', '1990-05-14', '123 Main St', '1234567890', 'john.doe@email.com', '2024-01-10'),
(2, 'Jane', 'Smith', '1985-08-21', '456 Oak St', '0987654321', 'jane.smith@email.com', '2024-01-12')

-- Create Accounts Table
CREATE TABLE Accounts (
    AccountNumber INT PRIMARY KEY,
    CustomerID INT,
    AccountType NVARCHAR(20),
    Balance DECIMAL(10,2),
    OpenDate DATE,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

-- Insert Sample Data into Accounts
INSERT INTO Accounts (AccountNumber, CustomerID, AccountType, Balance, OpenDate) VALUES
(1001, 1, 'Savings', 5000.00, '2024-06-01'),
(1002, 1, 'Checking', 2000.00, '2024-07-15'),
(2001, 2, 'Savings', 7000.00, '2024-05-20')

-- Create Transactions Table
CREATE TABLE Transactions (
    TransactionID INT PRIMARY KEY,
    AccountNumber INT,
    TransactionType NVARCHAR(20),
    Amount DECIMAL(10,2),
    TransactionDate DATE,
    FOREIGN KEY (AccountNumber) REFERENCES Accounts(AccountNumber)
);

-- Insert Sample Data into Transactions
INSERT INTO Transactions (TransactionID, AccountNumber, TransactionType, Amount, TransactionDate) VALUES
(1, 1001, 'Deposit', 1000.00, '2025-02-01'),
(2, 1001, 'Withdrawal', 500.00, '2025-02-02'),
(3, 1002, 'Deposit', 1500.00, '2025-02-03'),
(4, 2001, 'Deposit', 2000.00, '2025-02-05'),
(5, 1001, 'Withdrawal', 200.00, '2025-02-07');

-- Create Employees Table
CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY,
    FirstName NVARCHAR(50),
    LastName NVARCHAR(50),
    DateOfBirth DATE,
    Position NVARCHAR(50),
    Department NVARCHAR(50),
    Salary DECIMAL(10,2),
    HireDate DATE,
    Address NVARCHAR(255),
    PhoneNumber NVARCHAR(15),
    Email NVARCHAR(100),
    SupervisorID INT NULL,
    FOREIGN KEY (SupervisorID) REFERENCES Employees(EmployeeID)
);

-- Insert Sample Data into Employees
INSERT INTO Employees (EmployeeID, FirstName, LastName, DateOfBirth, Position, Department, Salary, HireDate, Address, PhoneNumber, Email, SupervisorID) VALUES
(1, 'Michael', 'Smith', '1980-03-22', 'Manager', 'Operations', 80000.00, '2020-06-15', '321 Birch St', '1231231234', 'michael.smith@email.com', NULL),
(2, 'Sarah', 'Johnson', '1992-11-10', 'Teller', 'Operations', 40000.00, '2020-08-01', '654 Cedar St', '4564564567', 'sarah.johnson@email.com', 1),
(3, 'David', 'Williams', '1985-04-17', 'Teller', 'Operations', 40000.00, '2020-02-20', '987 Maple St', '7897897890', 'david.williams@email.com', 1)


-- Query 1
SELECT C.CustomerID, C.FirstName + ' ' + C.LastName AS FullName, A.AccountNumber,
A.AccountType, A.Balance
FROM Customers C
INNER JOIN Accounts A ON C.CustomerID = A.CustomerID;
-- Query 2
SELECT CustomerID, COUNT(AccountNumber) AS TotalAccounts
FROM Accounts
GROUP BY CustomerID
ORDER BY TotalAccounts DESC;
-- Query 3
SELECT AccountNumber, SUM(Amount) AS TotalDeposits
FROM Transactions
WHERE TransactionType = 'Deposit'
GROUP BY AccountNumber
ORDER BY TotalDeposits DESC;
-- Query 4
SELECT C.CustomerID, C.FirstName, C.LastName
FROM Customers C
WHERE C.CustomerID IN (SELECT A.CustomerID FROM Accounts A WHERE A.Balance > 5000);
-- Query 5
SELECT E.Department, AVG(E.Salary) AS AvgSalary
FROM Employees E
GROUP BY E.Department
ORDER BY AvgSalary DESC;
-- Query 6
SELECT T.AccountNumber, COUNT(*) AS TransactionCount, SUM(T.Amount) AS
TotalTransactionAmount
FROM Transactions T
GROUP BY T.AccountNumber
HAVING COUNT(*) > 2;
-- Query 7
SELECT TOP 3 TransactionID,AccountNumber,TransactionType,Amount
FROM Transactions
ORDER BY TransactionDate DESC;
-- Query 8
SELECT C.CustomerID, C.FirstName, C.LastName, COUNT(T.TransactionID) AS TotalTransactions
FROM Customers C
INNER JOIN Accounts A ON C.CustomerID = A.CustomerID
INNER JOIN Transactions T ON A.AccountNumber = T.AccountNumber
GROUP BY C.CustomerID, C.FirstName, C.LastName
ORDER BY TotalTransactions DESC;
-- Query 9
SELECT FirstName, LastName
FROM Employees
WHERE EmployeeID = (SELECT SupervisorID FROM Employees WHERE EmployeeID = 2);
-- Query 10
SELECT E1.EmployeeID,
E1.FirstName AS EmployeeFirstName,
E1.LastName AS EmployeeLastName,
E2.FirstName AS SupervisorFirstName,
E2.LastName AS SupervisorLastName
FROM Employees E1
LEFT JOIN Employees E2 ON E1.SupervisorID = E2.EmployeeID;