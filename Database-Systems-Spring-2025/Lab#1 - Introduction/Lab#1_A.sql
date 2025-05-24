-- Create database Schema
USE master;
GO
CREATE DATABASE university;
GO
USE university;

-- q#1
create table student (
    rollnum varchar(10) primary key,
    name nvarchar(50),
    gender varchar(10),
    phone varchar(15)
);

create table attendance (
    rollnum varchar(10),
    date date,
    status char(1),
    classvenue int,
    foreign key (rollnum) references student(rollnum)
);

create table classvenue (
    id int primary key,
    building nvarchar(50),
    roomnum int,
    teacherid int
);

create table teacher (
    id int primary key,
    name nvarchar(50),
    designation nvarchar(50),
    department nvarchar(50)
);

-- q#2
alter table student add warningcount int;

-- q#3
insert into student (rollnum, name, gender, phone) 
values ('L162334', 'Fozan Shahid', 'Male', '03001234567');
insert into classvenue (id, building, roomnum, teacherid) 
values (3, 'CS', 5, 1);

update teacher 
set name = 'Dr. Kashif Zafar' 
where name = 'Kashif zafar';

delete from student where rollnum = 'L162334';
delete from student where rollnum = 'L164123';
delete from attendance where rollnum = 'L164124' and status = 'A';

-- q#4
alter table student add cnic varchar(15);
alter table student drop column phone;
alter table teacher add unique (name);
alter table student add check (gender in ('Male', 'Female'));
alter table attendance add check (status in ('A', 'P'));
