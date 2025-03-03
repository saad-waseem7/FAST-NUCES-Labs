-- 10 Simple Tasks

--1. distinct  (Get a list of unique customer cities from the "Customers" table)  
   select distinct city from Customers;

--2. not equal (`!=` or `<>`)  (Find all employees who are not from the "Sales" department)  
   select * from Employees where department <> 'Sales';

--3. between  (Get all products priced between Rs.10 and Rs.50 from the "Products" table)  
   select * from Products where price between 10 and 50;

--4. in  (Get orders where the status is either 'Pending', 'Processing', or 'Shipped')  
   select * from Orders where status in ('Pending', 'Processing', 'Shipped');

--5. set operations (union, intersect, except)  (Find all customers who have placed an order but are not in the VIP customer list)  
   select customer_id from Orders
   except
   select customer_id from VIP_Customers;

-- 6. cartesian product (Generate all possible combinations of employees and departments)  
   select * from Employees cross join Departments;

-- 7. like operator (Find all customers whose names start with 'J')  
   select * from Customers where name like 'J%';

-- 8. order by (Get all employees sorted by salary in descending order)  
   select * from Employees order by salary desc;

-- 9. top (Get the top 5 highest-paid employees)  
   select top 5 * from Employees order by salary desc;

-- 10. is null (Find all customers who do not have an assigned phone number)  
   select * from Customers where phone_number is null;

-- 5 Multiple Join Tasks

--   Get orders along with customer and product details.  

   select Orders.order_id, Customers.name, Products.product_name
   from Orders
   inner join Customers on Orders.customer_id = Customers.customer_id
   inner join Products on Orders.product_id = Products.product_id;

--   Get all employees and their department names, including employees with no assigned department.  

   select Employees.name, Departments.department_name
   from Employees
   left join Departments on Employees.department_id = Departments.department_id;

--   List all orders with customer names and optional shipping details.  

   select Orders.order_id, Customers.name, Shipments.tracking_number
   from Orders
   inner join Customers on Orders.customer_id = Customers.customer_id
   left join Shipments on Orders.order_id = Shipments.order_id;

--   Find all orders with customer and product details, and include optional discount information.  

   select Orders.order_id, Customers.name, Products.product_name, Discounts.discount_percentage
   from Orders
   inner join Customers on Orders.customer_id = Customers.customer_id
   inner join Products on Orders.product_id = Products.product_id
   left join Discounts on Orders.discount_id = Discounts.discount_id;

--   Get a list of employees, their department, their assigned projects, and their project manager.

   select Employees.name, Departments.department_name, Projects.project_name, Managers.name as manager_name
   from Employees
   inner join Departments on Employees.department_id = Departments.department_id
   inner join Projects on Employees.employee_id = Projects.employee_id
   inner join Managers on Projects.manager_id = Managers.manager_id;
