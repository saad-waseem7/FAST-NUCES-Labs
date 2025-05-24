-- Create database Schema
USE master;
GO
CREATE DATABASE ATM;
GO
USE ATM

create table UserType(
UserTypeID int primary key,
name varchar(20) not null
)

create table _User(
UserId int primary key,
name varchar(20) not null,
UserType int foreign key references UserType(UserTypeID),
phoneNum varchar(15) not null,
city varchar(20) not null
)

create table CardType(
cardTypeID int primary key,
name varchar(15),
description varchar(40) null
)

create table _Card(
cardNum Varchar(20) primary key,
cardTypeID int foreign key references  CardType(cardTypeID),
PIN varchar(4) not null,
expireDate date not null,
balance float not null
)

create table _UserCard(
UserId int foreign key references _User(UserId),
cardNum varchar(20) foreign key references _Card(cardNum),
primary key(cardNum)
)

create table TransactionType(
transTypeID int primary key,
typeName varchar(20) not null,
description varchar (40) null
)

create table _Transaction(
transId int primary key,
transDate date not null,
cardNum varchar(20) foreign key references _Card(cardNum),
amount int not null,
transType int foreign key references TransactionType(transTypeID)
)

insert dbo.UserType (UserTypeID, name) values (1, N'Silver')
insert dbo.UserType (UserTypeID, name) values (2, N'ld')
insert dbo.UserType (UserTypeID, name) values (3, N'Bronze')
insert dbo.UserType (UserTypeID, name) values (4, N'Common')
insert dbo._User (UserId, name, UserType, phoneNum, city) values (1, N'Ali', 2, N'03036067000', N'Narowal')
insert dbo._User (UserId, name, UserType, phoneNum, city) values (2, N'Ahmed', 1, N'03036047000', N'Lahore')
insert dbo._User (UserId, name, UserType, phoneNum, city) values (3, N'Aqeel', 3, N'03036063000', N'Karachi')
insert dbo._User (UserId, name, UserType, phoneNum, city) values (4, N'Usman', 4, N'03036062000', N'Sialkot')
insert dbo._User (UserId, name, UserType, phoneNum, city) values (5, N'Hafeez', 2, N'03036061000', N'Lahore')

insert dbo.CardType (cardTypeID, name, description) values (1, N'Debit', N'Spend Now, Pay Now')
insert dbo.CardType (cardTypeID, name, description) values (2, N'Credit', N'Spend Now, Pay later')
insert dbo.CardType (cardTypeID, name, description) values (3, N'Gift', N'Enjoy')
insert dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) values (N'1324327436569', 3, N'1770', CAST(N'2022-07-01' as Date), 43025.31)
insert dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) values (N'2324325423336', 3, N'0234', CAST(N'2020-03-02' as Date), 14425.62)
insert dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) values (N'2324325436566', 1, N'1234', CAST(N'2019-02-06' as Date), 34325.52)
insert dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) values (N'2324325666456', 2, N'1200', CAST(N'2021-02-05' as Date), 24325.3)
insert dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) values (N'2343243253436', 2, N'0034', CAST(N'2020-09-02' as Date), 34025.12)

insert dbo._UserCard (UserId, cardNum) values (1, N'1324327436569')
insert dbo._UserCard (UserId, cardNum) values (1, N'2343243253436')
insert dbo._UserCard (UserId, cardNum) values (2, N'2324325423336')
insert dbo._UserCard (UserId, cardNum) values (3, N'2324325436566')
insert dbo.TransactionType (transTypeID, typeName, description) values (1, N'Withdraw', null)
insert dbo.TransactionType (transTypeID, typeName, description) values (2, N'Deposit', null)
insert dbo.TransactionType (transTypeID, typeName, description) values (3, N'ScheduledDeposit', null)
insert dbo.TransactionType (transTypeID, typeName, description) values (4, N'Failed', null)

insert dbo._Transaction (transId, transDate, cardNum, amount, transType) values (1, CAST(N'2017-02-02' as Date), N'1324327436569', 500, 1)
insert dbo._Transaction (transId, transDate, cardNum, amount, transType) values (2, CAST(N'2018-02-03' as Date), N'2343243253436', 3000, 3)
insert dbo._Transaction (transId, transDate, cardNum, amount, transType) values (3, CAST(N'2017-05-06' as Date), N'2324325436566', 2500, 2)
insert dbo._Transaction (transId, transDate, cardNum, amount, transType) values (4, CAST(N'2016-09-09' as Date), N'2324325436566', 2000, 1)
insert dbo._Transaction (transId, transDate, cardNum, amount, transType) values (5, CAST(N'2015-02-10' as Date), N'2324325423336', 6000, 4)

Select * from UserType
Select * from _User
Select * from _UserCard
Select * from _Card
Select * from CardType
Select * from _Transaction
Select * from TransactionType

-- 1.Create a procedure to display all the user's details.

create procedure sp_DisplayAllUsers as
select u.*,
    ut.name as _type
from _User u
    join UserType ut on u.UserType = ut.UserTypeID;
EXEC sp_DisplayAllUsers;

-- 2.Create a procedure that takes user name and display his details.

create procedure sp_DisplayUserDetailsByName @UserName nvarchar(20) as
select u.*,
    ut.name as UserType
from _User u
    join UserType ut on u.UserType = ut.UserTypeID
where u.name = @UserName;
EXEC sp_DisplayUserDetailsByName 'Aqeel';

-- 3.Create a procedure that takes card number and display owner's name, phone number and city.

create procedure sp_DisplayCardOwnerDetails @CardNumber nvarchar(20) as
select u.name,
    u.phoneNum,
    u.city
from _User u
    join _UserCard uc on u.UserId = uc.UserId
where uc.cardNum = @CardNumber;
EXEC sp_DisplayCardOwnerDetails '2324325436566';

-- 4.Create a procedure that returns minimum balance in an output parameter.

create procedure sp_GetMinimumBalance @MinBalance float OUTPUT as
select @MinBalance = min(balance)
from _Card
declare @MinBalance float;
EXEC sp_GetMinimumBalance @MinBalance OUTPUT;
print @MinBalance

-- 5.Create a procedure that takes user name, id and returns no. of cards of that user in an output parameter.

create procedure getnumcardsforuser @name varchar(20),
@id int,
@numcards int output as begin
select @numcards = count(uc.cardNum)
from _UserCard uc
    join _User u on u.UserId = uc.UserId
where u.name = @name
    and u.UserId = @id
group by uc.UserId
end
declare @numcards int;
exec getnumcardsforuser 'Ali',
1,
@numcards output print @numcards

-- 6.Create a procedure Login that takes card number, PIN and returns the status in an output parameter. 
-- (@status =1 if card number and PIN is valid and @status=0 otherwise.(Hint: IF/ELSE).)

create procedure login @cardnum varchar(20),
@pin varchar(4),
@status int output as begin if exists (
    select *
    from _Card c
    where @cardnum = c.cardNum
        and @pin = c.PIN
)
set @status = 1;
else
set @status = 0;
end
declare @status int;
exec login '1324327436569',
'1770',
@status output print @status

-- 7.Create a procedure to update the PIN. The procedure takes Card Number, old PIN and new ValidPIN (Length 4) and print 'Updated PIN' if PIN gets updated or 'Error' otherwise.
-- (Google it if you don't know how to compare the Length).

create procedure updatepin @cardnum varchar(20),
@oldpin varchar(4),
@newpin varchar(4) as begin if len(@newpin) = 4
and exists (
    select 1
    from _Card
    where cardNum = @cardnum
        and PIN = @oldpin
) begin
update _Card
set PIN = @newpin
where cardNum = @cardnum;
print 'Updated PIN';
end
else begin print 'Error'
end
end exec updatepin '1324327436569',
'1770',
'1111'

-- 8. Create a procedure WithDraw using Login Procedure (Question#6), the procedure will take Card Number, PIN, amount for transaction. Now insert detail of the transaction in Transaction
-- Table if the transaction is successful with TransType =1(successful Transaction) and next transID (calculate the max transID and increment transID, then insert in table). If the transaction fails
-- insert TransType=4 (Failed Transaction). Update the balance against the card number accordingly.

create procedure withdraw @cardnum varchar(20),
@pin varchar(4),
@amount int as begin
declare @status int,
    @balance float,
    @nexttransid int exec login @cardnum,
    @pin,
    @status output if @status = 1 begin
select @balance = balance
from _Card
where cardNum = @cardnum if @balance >= @amount begin
update _Card
set balance = balance - @amount
where cardNum = @cardnum
select @nexttransid = max(transId) + 1
from _Transaction
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (
        @nexttransid,
        cast(getdate() as date),
        @cardnum,
        @amount,
        1
    ) print 'Withdrawal Successful'
end
else begin
select @nexttransid = max(transId) + 1
from _Transaction;
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (
        @nexttransid,
        cast(getdate() as date),
        @cardnum,
        @amount,
        4
    ) print 'Insufficient Balance'
end
end
else begin
select @nexttransid = max(transId) + 1
from _Transaction;
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (
        @nexttransid,
        cast(getdate() as date),
        @cardnum,
        @amount,
        4
    ) print 'Invalid Card Details';
end
end
go exec withdraw '1324327436569',
    '1770',
    1000