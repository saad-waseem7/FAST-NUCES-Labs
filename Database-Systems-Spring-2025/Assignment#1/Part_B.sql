-- Create database Schema
USE master;
GO
CREATE DATABASE Mart;
GO
USE Mart

-- Part A: Create basic tables with basic constraints
create table store (
    store_id int not null,
    city varchar(100),
    region varchar(50) default 'unknown'
);

create table product (
    product_id int not null,
    description varchar(500) not null,
    brand varchar(100)
);

create table sales (
    store_id int,
    product_id int,
    sales int,
    cost int,
    profit int,
    sales_date date default getdate()
);

-- Add Constraints using "Alter" Command
alter table store add constraint pk_store primary key (store_id);
alter table store alter column city varchar(100) not null;
alter table store add constraint unique_city_region unique (city, region);

alter table product add constraint pk_product primary key (product_id);

alter table sales add constraint chk_profit check (profit >= 0);
alter table sales add constraint fk_sales_store foreign key (store_id)
references store(store_id) on delete cascade on update no action;
alter table sales add constraint fk_sales_product foreign key (product_id)
references product(product_id) on delete cascade on update no action;

EXEC sp_rename 'sales.cost',  'purchase_cost', 'COLUMN';

-- Part B: Inserting Sample Data
insert into store (store_id, city, region) values 
(1, 'New York', 'East'), 
(2, 'Los Angeles', 'West'), 
(3, 'Chicago', 'Midwest'), 
(4, 'Houston', 'South'), 
(5, 'Phoenix', 'West'), 
(6, 'Philadelphia', 'East'), 
(7, 'San Antonio', 'South'), 
(8, 'San Diego', 'West'), 
(9, 'Dallas', 'South'), 
(10, 'San Jose', 'West'), 
(11, 'Austin', 'South'), 
(12, 'Jacksonville', 'South'), 
(13, 'Fort Worth', 'South'), 
(14, 'Columbus', 'Midwest'), 
(15, 'Charlotte', 'East'), 
(16, 'Indianapolis', 'Midwest'), 
(17, 'San Francisco', 'West'), 
(18, 'Seattle', 'West'), 
(19, 'Denver', 'West'), 
(20, 'Boston', 'East'); 

insert into product (product_id, description, brand) values 
(1, 'Laptop', 'Dell'), 
(2, 'Smartphone', 'Apple'), 
(3, 'Tablet', 'Samsung'), 
(4, 'Headphones', 'Sony'), 
(5, 'Smartwatch', 'Fitbit'), 
(6, 'Gaming Console', 'Microsoft'), 
(7, 'TV', 'LG'), 
(8, 'Camera', 'Canon'), 
(9, 'Router', 'Netgear'), 
(10, 'Monitor', 'HP'), 
(11, 'Printer', 'Epson'), 
(12, 'Keyboard', 'Logitech'), 
(13, 'Mouse', 'Razer'), 
(14, 'Speakers', 'Bose'), 
(15, 'Projector', 'BenQ'), 
(16, 'External HDD', 'Seagate'), 
(17, 'SSD', 'Samsung'), 
(18, 'Graphics Card', 'Nvidia'), 
(19, 'RAM', 'Corsair'), 
(20, 'Power Bank', 'Anker');

insert into sales (store_id, product_id, sales, purchase_cost, profit) values 
(1, 1, 50, 40000, 10000), 
(2, 2, 30, 30000, 9000), 
(3, 3, 40, 25000, 7500), 
(4, 4, 20, 15000, 5000), 
(5, 5, 35, 18000, 6000), 
(6, 6, 25, 22000, 7000), 
(7, 7, 15, 50000, 12000), 
(8, 8, 10, 8000, 2000), 
(9, 9, 28, 12000, 4000), 
(10, 10, 34, 17000, 5000), 
(11, 11, 21, 14000, 4500), 
(12, 12, 38, 9000, 3000), 
(13, 13, 44, 11000, 3500), 
(14, 14, 29, 32000, 9000), 
(15, 15, 23, 27000, 8000), 
(16, 16, 18, 13000, 4000), 
(17, 17, 31, 29000, 8500), 
(18, 18, 26, 35000, 11000), 
(19, 19, 37, 19000, 7000), 
(20, 20, 45, 10000, 3000); 

-- Part C: Given Queries 
select * from sales where purchase_cost > 15000;
select * from sales where profit between 4000 and 10000;
select * from sales where product_id in (5, 10, 15);
select * from store where region='west' order by city;
select top 10 * from Sales order by profit desc;
select * from store where region <> 'south';
select * from sales where sales <> 30;
select * from product where brand like '%s%';
select * from store where city like 's%';
select * from sales where purchase_cost > 20000 and profit < 8000;
select * from sales where sales > 35 or purchase_cost < 15000;
select distinct city from store union select distinct brand from product;
select city from store intersect select brand from product;
select city from store except select brand from product;
select * from sales where sales * purchase_cost > 500000;
