-- Question 1: Applying SQL Operations on the given database

-- INSERT Operations
INSERT INTO Product VALUES (NULL, 'Chicken Nuggets', 120, 100);  -- Might fail due to NULL ProductID
INSERT INTO Production VALUES (1,'1-2001', 300, '01-Feb-2021', '01-Feb-2022');  -- Success
INSERT INTO Production VALUES (1, NULL, 300, '01-Feb-2021', '01-Feb-2022');  -- Fails due to NULL BatchNo (Primary Key)
INSERT INTO Customer VALUES (1,'Packages', 'DHA', '042-31234567');  -- Fails due to duplicate CustomerID
INSERT INTO `Order` VALUES (5, 10, 1, '09-Feb-2021');  -- Fails due to non-existent CustomerID 10

-- DELETE Operations (CASCADE)
DELETE FROM Product WHERE ProductID=2;  -- Deletes related Production & Order records
DELETE FROM Customer WHERE CustomerID=1;  -- Deletes related orders
DELETE FROM Production WHERE BatchID='1-1002';  -- Fails (BatchID column does not exist, should be BatchNo)
DELETE FROM `Order` WHERE CustomerID=1 OR ProductID=1;  -- Deletes relevant orders
DELETE FROM `Order` WHERE OrderNo=4;  -- Fails (OrderNo=4 does not exist)

-- DELETE Operations (SET NULL)
DELETE FROM Product WHERE ProductID=2;  -- Sets related records' ProductID to NULL
DELETE FROM Customer WHERE CustomerID=1;  -- Sets related records' CustomerID to NULL
DELETE FROM Production WHERE BatchID='1-1002';  -- Fails (wrong column name)
DELETE FROM `Order` WHERE CustomerID=1 OR ProductID=1;  -- Sets related records' foreign keys to NULL
DELETE FROM `Order` WHERE OrderNo=4;  -- Fails (OrderNo=4 does not exist)

-- UPDATE Operations (CASCADE)
UPDATE `Order` SET CustomerID=10 WHERE CustomerId=2;  -- Fails (CustomerID 10 does not exist)
UPDATE Product SET ProductID=21 WHERE ProductID=3;  -- Updates ProductID, cascades changes to dependent tables
UPDATE `Order` SET OrderDate=NULL WHERE ProductID=1;  -- Success
UPDATE Production SET CustomerID=1 WHERE BatchID='1-1002';  -- Fails (CustomerID column does not exist)
UPDATE Production SET BatchNo=NULL WHERE UnitsProduced=6000;  -- Fails (BatchNo is PK, cannot be NULL)

-- Question 2: Defining Domains & Populating Tables
CREATE TABLE Publisher (
    PublisherID INT PRIMARY KEY,
    PublisherName VARCHAR(100),
    Address VARCHAR(255)
);

CREATE TABLE Author (
    AuthorID INT PRIMARY KEY,
    AuthorName VARCHAR(100),
    Gender CHAR(1),
    BirthDate DATE,
    Country VARCHAR(50)
);

CREATE TABLE Book (
    ISBN VARCHAR(13) PRIMARY KEY,
    AuthorID INT,
    PublisherID INT,
    PublishDate DATE,
    BookTitle VARCHAR(255),
    FOREIGN KEY (AuthorID) REFERENCES Author(AuthorID),
    FOREIGN KEY (PublisherID) REFERENCES Publisher(PublisherID)
);

-- Publisher data
INSERT INTO Publisher VALUES 
(1, 'OReilly', 'USA'),
(2, 'Pearson', 'UK'),
(3, 'Manning', 'USA'),
(4, 'Wiley', 'USA'),
(5, 'No Starch Press', 'USA');

-- Author data
INSERT INTO Author VALUES 
(1, 'Dwayne Johnson', 'M', '1980-05-21', 'USA'),
(2, 'Steve Smith', 'M', '1975-10-08', 'Canada'),
(3, 'David Laid', 'M', '1982-03-15', 'UK'),
(4, 'Sarah Safari', 'F', '1979-06-23', 'Australia'),
(5, 'Michael Jordan', 'M', '1985-11-12', 'USA');

-- Book data
INSERT INTO Book VALUES 
('978-3-16-148410-0', 1, 1, '2022-06-01', 'Database Essentials'),
('978-1-80-107722-1', 2, 2, '2023-01-15', 'Web Development with Python'),
('978-1-61-729609-4', 3, 3, '2022-09-20', 'Machine Learning Fundamentals'),
('978-0-73-561967-8', 4, 4, '2022-04-10', 'Data Analysis with R'),
('978-1-59-327950-9', 5, 5, '2023-02-28', 'Hacking: The Art of Exploitation');