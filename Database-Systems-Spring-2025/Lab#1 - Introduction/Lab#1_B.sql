-- Create database Schema
USE master;
GO
CREATE DATABASE purchase_management_system;
GO
USE purchase_management_system

CREATE TABLE salesman (
    salesman_id INT PRIMARY KEY,
    name VARCHAR(50),
    city VARCHAR(50),
    commission DECIMAL(4,2)
);


CREATE TABLE customers (
    customer_id INT PRIMARY KEY,
    cust_name VARCHAR(50),
    city VARCHAR(50),
    grade INT,
    salesman_id INT,
    FOREIGN KEY (salesman_id) REFERENCES salesman(salesman_id)
);

CREATE TABLE orders (
    ord_no INT PRIMARY KEY,
    purch_amt DECIMAL(10,2),
    ord_date DATE,
    customer_id INT,
    salesman_id INT,
    FOREIGN KEY (salesman_id) REFERENCES salesman(salesman_id),
	FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

INSERT INTO salesman (salesman_id, name, city, commission) 
VALUES
(5001, 'James Hoog', 'New York', 0.15),
(5002, 'Nail Knite', 'Paris', 0.13),
(5005, 'Pit Alex', 'London', 0.11),
(5006, 'Mc Lyon', 'Paris', 0.14),
(5007, 'Paul Adam', 'San Jose', 0.13),
(5003, 'Lauson Hen', 'San Jose', 0.12);

INSERT INTO customers (customer_id, cust_name, city, grade, salesman_id) 
VALUES
(3002, 'Nick Rimando', 'New York', 100, 5001),
(3007, 'John Brad Davis', 'New York', 200, 5001),
(3005, 'Graham Zusi', 'California', 200, 5002),
(3008, 'Julian Green', 'London', 300, 5002),
(3004, 'Fabian Johnson', 'Paris', 300, 5006),
(3009, 'Geoff Cameron', 'Berlin', 100, 5003),
(3003, 'Jozy Altidor', 'Moscow', 200, 5007),
(3001, 'John Brad Guzan', 'London', NULL, 5005);
INSERT INTO orders (ord_no, purch_amt, ord_date, customer_id, salesman_id) 
VALUES
(70001, 150.5, '2012-10-05', 3005, 5002),
(70009, 270.65, '2011-09-10', 3001, 5005),
(70002, 65.26, '2014-10-05', 3002, 5001),
(70004, 110.5, '2011-08-17', 3009, 5003),
(70007, 948.5, '2012-09-10', 3005, 5002),
(70005, 2400.6, '2010-07-27', 3007, 5001),
(70008, 5760, '2013-09-10', 3002, 5001),
(70010, 1983.43, '2010-10-10', 3004, 5006),
(70003, 2480.4, '2013-10-10', 3009, 5003),
(70012, 250.45, '2010-06-27', 3008, 5002),
(70011, 75.29, '2014-08-17', 3003, 5007),
(70013, 3045.6, '2010-04-25', 3002, 5001);

Select * from salesman
select * from customers
Select * from orders

-- Part#B Queries

select * from salesman where city = 'Paris';
select * from salesman where name like 'J%' and city = 'New York';
select * from customers where cust_name like '%Brad%';
select * from orders where ord_no like '7000%';
select * from salesman where city like '%York';
select * from customers where city like '%o%';
select top 1 * from salesman order by commission asc;
update salesman 
set commission = round(commission + (commission * 0.02), 2) --help used
where commission > 0.13;

