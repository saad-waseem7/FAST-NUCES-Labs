-- Create database
USE master;
GO

CREATE DATABASE SuperDogCarbonDB;
GO

USE SuperDogCarbonDB;
GO

-- 1. Organization
CREATE TABLE Organization (
    organization_id INT PRIMARY KEY IDENTITY(1,1),
    organization_name VARCHAR(255) NOT NULL,
    industry_type VARCHAR(100)
);

-- 2. Site
CREATE TABLE Site (
    site_id INT PRIMARY KEY IDENTITY(1,1),
    organization_id INT NOT NULL,
    site_name VARCHAR(255) NOT NULL,
    location VARCHAR(255),
    FOREIGN KEY (organization_id) REFERENCES Organization(organization_id)
);

-- 3. Supplier
CREATE TABLE Supplier (
    supplier_id INT PRIMARY KEY IDENTITY(1,1),
    supplier_name VARCHAR(255) NOT NULL,
    region VARCHAR(100)
);

-- 4. Emission_Scope
CREATE TABLE Emission_Scope (
    scope_id INT PRIMARY KEY IDENTITY(1,1),
    scope_type VARCHAR(50) NOT NULL CHECK (scope_type IN ('Scope 1', 'Scope 2', 'Scope 3')),
    description TEXT
);

-- 5. Emission_Source
CREATE TABLE Emission_Source (
    source_id INT PRIMARY KEY IDENTITY(1,1),
    source_type VARCHAR(100) NOT NULL,
    unit_of_measure VARCHAR(50),
    default_emission_factor DECIMAL(10, 4)
);

-- 6. Emission_Record
CREATE TABLE Emission_Record (
    record_id INT PRIMARY KEY IDENTITY(1,1),
    site_id INT NOT NULL,
    supplier_id INT NOT NULL,
    scope_id INT NOT NULL,
    source_id INT NOT NULL,
    record_date DATE NOT NULL,
    quantity_used DECIMAL(12, 2) NOT NULL,
    emission_factor DECIMAL(10, 4) NOT NULL,
    calculated_emission AS (quantity_used * emission_factor) PERSISTED,
    FOREIGN KEY (site_id) REFERENCES Site(site_id),
    FOREIGN KEY (supplier_id) REFERENCES Supplier(supplier_id),
    FOREIGN KEY (scope_id) REFERENCES Emission_Scope(scope_id),
    FOREIGN KEY (source_id) REFERENCES Emission_Source(source_id)
);

-- 7. Emission_Target (optional for planning/strategy)
CREATE TABLE Emission_Target (
    target_id INT PRIMARY KEY IDENTITY(1,1),
    organization_id INT NOT NULL,
    scope_id INT NOT NULL,
    year INT NOT NULL,
    emission_limit DECIMAL(12, 2) NOT NULL,
    FOREIGN KEY (organization_id) REFERENCES Organization(organization_id),
    FOREIGN KEY (scope_id) REFERENCES Emission_Scope(scope_id)
);

USE SuperDogCarbonDB;
GO

-- 1. Insert into Organization
INSERT INTO Organization (organization_name, industry_type)
VALUES 
('EcoCorp Ltd.', 'Manufacturing'),
('GreenWare Inc.', 'Software'),
('UrbanPower Co.', 'Energy'),
('CleanFoods Ltd.', 'Food Processing'),
('TransportMax', 'Logistics'),
('SkyHigh Airlines', 'Aviation'),
('SmartHome Solutions', 'Electronics'),
('BuildBright', 'Construction'),
('TreeLine Apparel', 'Fashion'),
('AquaFlow Utilities', 'Water Management');

-- 2. Insert into Site
INSERT INTO Site (organization_id, site_name, location)
VALUES
(1, 'EcoCorp HQ', 'New York'),
(1, 'EcoCorp Plant A', 'New Jersey'),
(2, 'GreenWare Hub', 'San Francisco'),
(3, 'UrbanPower Plant 1', 'Texas'),
(4, 'CleanFoods Factory', 'Chicago'),
(5, 'TransportMax Warehouse', 'Detroit'),
(6, 'SkyHigh Terminal', 'Atlanta'),
(7, 'SmartHome Factory', 'Seattle'),
(8, 'BuildBright Site A', 'Houston'),
(9, 'TreeLine Studio', 'Los Angeles');

-- 3. Insert into Supplier
INSERT INTO Supplier (supplier_name, region)
VALUES
('PowerGrid Inc.', 'North America'),
('BioFuel Systems', 'Europe'),
('ClearEnergy', 'Asia'),
('FreshWater Corp.', 'North America'),
('GreenTransport Ltd.', 'Europe'),
('RecyclePro', 'North America'),
('SolarPeak', 'Asia'),
('CarbonNeutral Freight', 'South America'),
('EcoDeliveries', 'Africa'),
('WindFlow Partners', 'Oceania');

-- 4. Insert into Emission_Scope
INSERT INTO Emission_Scope (scope_type, description)
VALUES
('Scope 1', 'Direct emissions from owned or controlled sources'),
('Scope 2', 'Indirect emissions from the generation of purchased electricity'),
('Scope 3', 'Other indirect emissions such as those from supply chains');

-- 5. Insert into Emission_Source
INSERT INTO Emission_Source (source_type, unit_of_measure, default_emission_factor)
VALUES
('Diesel Fuel', 'liters', 2.68),
('Electricity', 'kWh', 0.5),
('Natural Gas', 'cubic meters', 1.9),
('Air Travel', 'passenger-km', 0.18),
('Freight Shipping', 'ton-km', 0.1),
('Office Equipment', 'unit', 12.5),
('Refrigerant Leak', 'kg', 1430),
('Food Waste', 'kg', 4.0),
('Employee Commute', 'km', 0.12),
('Water Usage', 'cubic meters', 0.5);

-- 6. Insert into Emission_Record
INSERT INTO Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
VALUES
(1, 1, 2, 2, '2024-01-15', 10000, 0.5),
(2, 2, 1, 1, '2024-01-20', 5000, 2.68),
(3, 3, 3, 9, '2024-02-01', 2000, 0.12),
(4, 4, 2, 2, '2024-02-10', 8000, 0.5),
(5, 5, 3, 5, '2024-03-05', 12000, 0.1),
(6, 6, 1, 4, '2024-03-10', 1500, 0.18),
(7, 7, 1, 3, '2024-03-20', 3000, 1.9),
(8, 8, 3, 6, '2024-04-01', 100, 12.5),
(8, 8, 3, 7, '2024-04-01', 100, 12.5),
(8, 8, 3, 8, '2024-04-01', 100, 12.5),
(9, 9, 3, 8, '2024-04-10', 2500, 4.0),
(10, 10, 1, 7, '2024-04-15', 50, 1430);

-- 7. Insert into Emission_Target
INSERT INTO Emission_Target (organization_id, scope_id, year, emission_limit)
VALUES
(1, 1, 2025, 25000),
(2, 2, 2025, 15000),
(3, 3, 2025, 10000),
(4, 1, 2025, 5000),
(5, 3, 2025, 12000),
(6, 1, 2025, 8000),
(7, 2, 2025, 6000),
(8, 3, 2025, 10000),
(9, 2, 2025, 9000),
(10, 1, 2025, 3000);

-- PART # 1

-- Task 1: Insert two rows using a transaction

BEGIN TRANSACTION;
BEGIN TRY
    INSERT INTO Emission_Record (site_id, record_date, emission_factor)
    VALUES (101, '2025-05-10', 120.5);

    INSERT INTO Emission_Record (site_id, record_date, emission_factor)
    VALUES (102, '2025-05-10', 98.7);

    COMMIT;
    PRINT 'Both inserts succeeded.';
END TRY
BEGIN CATCH
    ROLLBACK;
    PRINT 'Error occurred, both inserts rolled back.';
END CATCH;

--Task 2: Update two tables atomically

ALTER TABLE Site ADD total_emissions DECIMAL(12,2) DEFAULT 0;
BEGIN TRANSACTION;
BEGIN TRY
    UPDATE Site
    SET total_emissions = total_emissions + 50
    WHERE site_id = 1;    COMMIT;
    PRINT 'Emissions updated successfully.';
END TRY
BEGIN CATCH
    ROLLBACK;
    PRINT 'Error occurred. Rollback performed.';
end catch;

-- Task 3: Use SAVEPOINT in insert

BEGIN TRANSACTION;
BEGIN TRY
    INSERT INTO Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    VALUES (1, 3, 2, 2, '2025-05-10', 6000, 0.5);

    SAVE TRANSACTION SP1;

    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (NULL, 3, 2, 2, '2025-05-10', 6000, 0.5);

    commit;
end try
begin catch
    rollback transaction SP1;
    commit;
    print 'Second insert failed. Rolled back to SP1. First insert remains.';
end catch;

-- Task 4: TRY…CATCH with failed insert

begin try
    begin transaction;

    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (2, 2, 1, 1, '2025-05-10', 4500, 2.68);

    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (2, NULL, 1, 1, '2025-05-10', 1000, 2.68);    COMMIT;
END TRY
BEGIN CATCH
    ROLLBACK;
    PRINT 'Transaction failed and rolled back.';
end catch;

-- Task 5: Manual ROLLBACK test

begin transaction;

update Emission_Record
set quantity_used = 7777
where record_id = 1;

SELECT * FROM Emission_Record WHERE record_id = 1;
ROLLBACK;
SELECT * FROM Emission_Record WHERE record_id = 1;

-- Task 6: Carbon credit transfer between organizations

CREATE TABLE OrganizationCredits (
    org_id INT PRIMARY KEY,
    credits INT NOT NULL
);

begin transaction;
declare @credits INT;
select @credits = credits from OrganizationCredits where org_id = 1;

if @credits >= 100
begin
    update OrganizationCredits set credits = credits - 100 where org_id = 1;
    update OrganizationCredits set credits = credits + 100 where org_id = 2;
    commit;
    print 'Transfer completed.';
end
else
begin
    rollback;
    print 'Not enough credits. Transfer canceled.';
end

-- Task 7: Insert into Site and related SiteManager table

CREATE TABLE SiteManagers (
    manager_id INT PRIMARY KEY,
    site_id INT FOREIGN KEY REFERENCES Site(site_id),
    name VARCHAR(255)
);

begin transaction;
begin try
    insert into Site (organization_id, site_name, location)
    values (1, 'EcoCorp Lab', 'Boston');

    declare @newSiteId INT = SCOPE_IDENTITY();

    insert into SiteManagers (manager_id, site_id, name)
    values (999, @newSiteId, 'Mr. Barkley');

    commit;
end try
begin catch
    rollback;
    print 'Insert failed. Rolled back.';
end catch;

--Task 8: Multiple SAVEPOINTs in inserts

begin transaction;
begin try
    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (5, 5, 1, 1, '2025-05-10', 1000, 2.68);
    save transaction S1;

    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (6, 6, 2, 2, '2025-05-10', 2000, 0.5);
    save transaction S2;

    insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
    values (NULL, 7, 3, 3, '2025-05-10', 3000, 1.9);

    commit;
end try
begin catch
    rollback transaction S2;
    commit;
    print 'Third insert failed. Rolled back to S2.';
end catch;

-- Task 9: Nested BEGIN TRANSACTION test

BEGIN TRANSACTION;
BEGIN TRY
    UPDATE Site SET total_emissions = total_emissions + 10 WHERE site_id = 1;

    BEGIN TRANSACTION;
    update Site set total_emissions = total_emissions + 20 where site_id = 1;
    commit;  

    rollback;  
    print 'Outer rollback undid all changes.';
end try
begin catch
    rollback;
    print 'Error occurred.';
end catch;

-- Task 10: Stored Procedure

CREATE PROCEDURE ProcessCarbonData
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

        insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
        values (3, 3, 1, 1, '2025-05-10', 900, 2.68);

        insert into Emission_Record (site_id, supplier_id, scope_id, source_id, record_date, quantity_used, emission_factor)
        values (NULL, 3, 1, 1, '2025-05-10', 100, 2.68);        COMMIT;
    END TRY
    BEGIN CATCH
        ROLLBACK;
        PRINT 'Procedure failed. Rolled back.';
    END CATCH
END;
