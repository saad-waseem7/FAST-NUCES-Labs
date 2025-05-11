-- Create database Schema
USE master;
GO
CREATE DATABASE SuperDogCarbonDB;
GO
USE SuperDogCarbonDB;
GO

-- 1. Organization
CREATE TABLE Organization (
    organization_id int PRIMARY KEY IDENTITY(1,1),
    organization_name VARCHAR(255) NOT NULL,
    industry_type VARCHAR(100)
);

-- 2. Site
CREATE TABLE Site (
    site_id int PRIMARY KEY IDENTITY(1,1),
    organization_id int NOT NULL,
    site_name VARCHAR(255) NOT NULL,
    location VARCHAR(255),
    FOREIGN KEY (organization_id) REFERENCES Organization(organization_id)
);

-- 3. Supplier
CREATE TABLE Supplier (
    supplier_id int PRIMARY KEY IDENTITY(1,1),
    supplier_name VARCHAR(255) NOT NULL,
    region VARCHAR(100)
);

-- 4. Emission_Scope
CREATE TABLE Emission_Scope (
    scope_id int PRIMARY KEY IDENTITY(1,1),
    scope_type VARCHAR(50) NOT NULL CHECK (scope_type IN ('Scope 1', 'Scope 2', 'Scope 3')),
    description TEXT
);

-- 5. Emission_Source
CREATE TABLE Emission_Source (
    source_id int PRIMARY KEY IDENTITY(1,1),
    source_type VARCHAR(100) NOT NULL,
    unit_of_measure VARCHAR(50),
    default_emission_factor DECIMAL(10, 4)
);

-- 6. Emission_Record
CREATE TABLE Emission_Record (
    record_id int PRIMARY KEY IDENTITY(1,1),
    site_id int NOT NULL,
    supplier_id int NOT NULL,
    scope_id int NOT NULL,
    source_id int NOT NULL,
    record_date DATE NOT NULL,
    quantity_used DECIMAL(12, 2) NOT NULL,
    emission_factor DECIMAL(10, 4) NOT NULL,
    calculated_emission as (quantity_used * emission_factor) PERSISTED,
    FOREIGN KEY (site_id) REFERENCES Site(site_id),
    FOREIGN KEY (supplier_id) REFERENCES Supplier(supplier_id),
    FOREIGN KEY (scope_id) REFERENCES Emission_Scope(scope_id),
    FOREIGN KEY (source_id) REFERENCES Emission_Source(source_id)
);

-- 7. Emission_Target (optional for planning/strategy)
CREATE TABLE Emission_Target (
    target_id int PRIMARY KEY IDENTITY(1,1),
    organization_id int NOT NULL,
    scope_id int NOT NULL,
    year int NOT NULL,
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

-- Part 1:

-- 1. 

create trigger BlockDuplicateRecords on Emission_Record instead of
insert as begin if exists (
        select 1
        from Emission_Record r
            join inserted i on r.site_id = i.site_id
            and r.source_id = i.source_id
            and r.record_date = i.record_date
    ) begin print 'Duplicate entry blocked!';
end
else begin
insert into Emission_Record (site_id, source_id, record_date, emission_factor)
select site_id,
    source_id,
    record_date,
    emission_factor
from inserted;
end
end;

-- 2.

create function fn_GetEmissionCategory (@emission FLOAT) returns varchar(20) as begin
declare @category varchar(20) if @emission < 500
set @category = 'Low'
    else if @emission < 5000
set @category = 'Moderate'
    else
set @category = 'High' return @category
end;

-- Usage:

select *,
       dbo.fn_GetEmissionCategory(emission_factor) as category
from Emission_Record;

-- 3.

alter table Emission_Record
ADD emission_category as dbo.fn_GetEmissionCategory(emission_factor) PERSISTED;

-- 4.

create function fn_ComputeRiskScore (@emission FLOAT)
returns float as
begin
    return @emission * 2
end;

-- Usage:
alter table Emission_Record
ADD risk_score as dbo.fn_ComputeRiskScore(emission_factor) PERSISTED;

-- 5.
create trigger EmergencyFuelBurnTrigger on Emission_Record
after
insert,
    update as begin
insert into Emergency_Alerts (record_id, alert_message)
select i.record_id,
    'Emergency Burn Detected'
from inserted i
where i.emission_factor > 20000;
update s
set s.source_type = left(s.source_type + ' - Emergency Burn', 50)
from Emission_Source s
    join inserted i on s.source_id = i.source_id
where i.emission_factor > 20000;
end;

-- Part 2:
-- 1. 

create table LudoGamePlay (
    game_id int IDENTITY PRIMARY KEY,
    player_id int,
    dice_roll int,
    position int
);

-- 2.

create function CalculateNewPosition (@current int, @dice int)
returns int
as
begin
    declare @new int = @current + @dice
    if @new > 100
        set @new = 100
    return @new
end;

-- 3.

create trigger UpdatePosition
on LudoGamePlay
after insert as
begin
    update L
    set position = dbo.CalculateNewPosition(
        isnull((
            select top 1 position from LudoGamePlay
            where player_id = L.player_id and game_id < L.game_id
            order by game_id desc
        ), 0),
        L.dice_roll
    )
    from LudoGamePlay L
    join inserted i on L.game_id = i.game_id
end;

-- 4.

create procedure PlayTurn as begin
declare @last int = (
        select top 1 player_id
        from LudoGamePlay
        order by game_id desc
    )
declare @next int = case
        when @last = 1 then 2
        else 1
    end
declare @roll int = floor(rand() * 6 + 1)
insert into LudoGamePlay (player_id, dice_roll)
values (@next, @roll)
end;

-- 5.

EXEC PlayTurn;