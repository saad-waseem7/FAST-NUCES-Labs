-- Create database Schema
USE master;
GO
CREATE DATABASE Hospital;
GO
USE Hospital;

CREATE TABLE Doctor (
    DoctorID INT PRIMARY KEY,
    Name VARCHAR(70),
    Age INT CHECK (Age BETWEEN 25 AND 100),
    Specialization VARCHAR(70)
);

CREATE TABLE Patient (
    PatientID INT PRIMARY KEY,
    Name VARCHAR(70),
    Age INT,
    DoctorID INT,
    FOREIGN KEY (DoctorID) REFERENCES Doctor(DoctorID)
);

ALTER TABLE Patient
    ADD CONSTRAINT FK_DoctorID FOREIGN KEY (DoctorID)
    REFERENCES Doctor(DoctorID)
    ON DELETE CASCADE
    ON UPDATE SET NULL;