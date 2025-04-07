create database ATM
use ATM

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

INSERT dbo.UserType (UserTypeID, name) VALUES (1, N'Silver')
INSERT dbo.UserType (UserTypeID, name) VALUES (2, N'ld')
INSERT dbo.UserType (UserTypeID, name) VALUES (3, N'Bronze')
INSERT dbo.UserType (UserTypeID, name) VALUES (4, N'Common')
INSERT dbo._User (UserId, name, UserType, phoneNum, city) VALUES (1, N'Ali', 2, N'03036067000', N'Narowal')
INSERT dbo._User (UserId, name, UserType, phoneNum, city) VALUES (2, N'Ahmed', 1, N'03036047000', N'Lahore')
INSERT dbo._User (UserId, name, UserType, phoneNum, city) VALUES (3, N'Aqeel', 3, N'03036063000', N'Karachi')
INSERT dbo._User (UserId, name, UserType, phoneNum, city) VALUES (4, N'Usman', 4, N'03036062000', N'Sialkot')
INSERT dbo._User (UserId, name, UserType, phoneNum, city) VALUES (5, N'Hafeez', 2, N'03036061000', N'Lahore')

INSERT dbo.CardType (cardTypeID, name, description) VALUES (1, N'Debit', N'Spend Now, Pay Now')
INSERT dbo.CardType (cardTypeID, name, description) VALUES (2, N'Credit', N'Spend Now, Pay later')
INSERT dbo.CardType (cardTypeID, name, description) VALUES (3, N'Gift', N'Enjoy')
INSERT dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1324327436569', 3, N'1770', CAST(N'2022-07-01' AS Date), 43025.31)
INSERT dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'2324325423336', 3, N'0234', CAST(N'2020-03-02' AS Date), 14425.62)
INSERT dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'2324325436566', 1, N'1234', CAST(N'2019-02-06' AS Date), 34325.52)
INSERT dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'2324325666456', 2, N'1200', CAST(N'2021-02-05' AS Date), 24325.3)
INSERT dbo._Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'2343243253436', 2, N'0034', CAST(N'2020-09-02' AS Date), 34025.12)

INSERT dbo._UserCard (UserId, cardNum) VALUES (1, N'1324327436569')
INSERT dbo._UserCard (UserId, cardNum) VALUES (1, N'2343243253436')
INSERT dbo._UserCard (UserId, cardNum) VALUES (2, N'2324325423336')
INSERT dbo._UserCard (UserId, cardNum) VALUES (3, N'2324325436566')
INSERT dbo.TransactionType (transTypeID, typeName, description) VALUES (1, N'Withdraw', NULL)
INSERT dbo.TransactionType (transTypeID, typeName, description) VALUES (2, N'Deposit', NULL)
INSERT dbo.TransactionType (transTypeID, typeName, description) VALUES (3, N'ScheduledDeposit', NULL)
INSERT dbo.TransactionType (transTypeID, typeName, description) VALUES (4, N'Failed', NULL)

INSERT dbo._Transaction (transId, transDate, cardNum, amount, transType) VALUES (1, CAST(N'2017-02-02' AS Date), N'1324327436569', 500, 1)
INSERT dbo._Transaction (transId, transDate, cardNum, amount, transType) VALUES (2, CAST(N'2018-02-03' AS Date), N'2343243253436', 3000, 3)
INSERT dbo._Transaction (transId, transDate, cardNum, amount, transType) VALUES (3, CAST(N'2017-05-06' AS Date), N'2324325436566', 2500, 2)
INSERT dbo._Transaction (transId, transDate, cardNum, amount, transType) VALUES (4, CAST(N'2016-09-09' AS Date), N'2324325436566', 2000, 1)
INSERT dbo._Transaction (transId, transDate, cardNum, amount, transType) VALUES (5, CAST(N'2015-02-10' AS Date), N'2324325423336', 6000, 4)

Select * from UserType
Select * from _User
Select * from _UserCard
Select * from _Card
Select * from CardType
Select * from _Transaction
Select * from TransactionType

-- 1.Create a procedure to display all the user�s details.

create procedure sp_DisplayAllUsers as
select u.*, ut.name as _type from _User u
join UserType ut on u.UserType = ut.UserTypeID;
EXEC sp_DisplayAllUsers;

-- 2.Create a procedure that takes user name and display his details.

create procedure sp_DisplayUserDetailsByName
@UserName nvarchar(20) as
select u.*, ut.name as UserType from _User u
join UserType ut on u.UserType = ut.UserTypeID
where u.name = @UserName;
EXEC sp_DisplayUserDetailsByName 'Aqeel';

-- 3.Create a procedure that takes card number and display owner�s name, phone number and city.

create procedure sp_DisplayCardOwnerDetails
@CardNumber nvarchar(20) as
select u.name, u.phoneNum, u.city from _User u
join _UserCard uc on u.UserId = uc.UserId
where uc.cardNum = @CardNumber;
EXEC sp_DisplayCardOwnerDetails '2324325436566';

-- 4.Create a procedure that returns minimum balance in an output parameter.

create procedure sp_GetMinimumBalance
@MinBalance float OUTPUT as
select @MinBalance = min(balance) from _Card
declare @MinBalance float;
EXEC sp_GetMinimumBalance @MinBalance OUTPUT;
print @MinBalance

-- 5.Create a procedure that takes user name, id and returns no. of cards of that user in an output parameter.

create procedure getnumcardsforuser
@name varchar(20), @id int, @numcards int output as
select @numcards = count(uc.cardNum) from _User u
join _UserCard uc on u.UserId = uc.UserId
where u.name = @name and u.UserId = @id
declare @numcards int;
exec getnumcardsforuser 'Ali', 1, @numcards output
print @numcards


-- 6.Create a procedure Login that takes card number, PIN and returns the status in an output parameter. 
-- @status =1 if card number and PIN is valid and @status=0 otherwise.(Hint: IF/ELSE).

create procedure login
@cardnum varchar(20), @pin varchar(4), @status int output as
if exists (select 1 from _Card where cardNum = @cardnum and PIN = @pin)
begin set @status = 1;
else set @status = 0;

declare @status int;
exec login '1324327436569', '1770', @status output
print @status

-- 7.Create a procedure to update the PIN. The procedure takes Card Number, old PIN and new ValidPIN (Length 4) and print �Updated PIN� if PIN gets updated or �Error� otherwise.
-- (Google it if you don�t know how to compare the Length).

create procedure updatepin
@cardnum varchar(20), @oldpin varchar(4), @newpin varchar(4) as
begin if len(@newpin) = 4 and exists (select 1 from _Card where cardNum = @cardnum and PIN = @oldpin) begin
update _Card set PIN = @newpin where cardNum = @cardnum;
print 'Updated PIN'; end
else
begin print 'Error' end
end

exec updatepin '1324327436569', '1770', '1111'

-- 8. Create a procedure WithDraw using Login Procedure (Question#6), the procedure will take Card Number, PIN, amount for transaction. Now insert detail of the transaction in Transaction
-- Table if the transaction is successful with TransType =1(successful Transaction) and next transID (calculate the max transID and increment transID, then insert in table). If the transaction fails
-- insert TransType=4 (Failed Transaction). Update the balance against the card number accordingly.

create procedure withdraw
@cardnum varchar(20), @pin varchar(4), @amount int as
begin declare @status int, @balance float, @nexttransid int
exec login @cardnum, @pin, @status output
if @status = 1 begin
select @balance = balance from _Card where cardNum = @cardnum
if @balance >= @amount begin
update _Card set balance = balance - @amount where cardNum = @cardnum
select @nexttransid = max(transId) + 1 from _Transaction
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (@nexttransid, cast(getdate() as date), @cardnum, @amount, 1)
print 'Withdrawal Successful' end
else begin
select @nexttransid = max(transId) + 1 from _Transaction;
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (@nexttransid, cast(getdate() as date), @cardnum, @amount, 4)
print 'Insufficient Balance' end
end
else begin
select @nexttransid = max(transId) + 1 from _Transaction;
insert into _Transaction (transId, transDate, cardNum, amount, transType)
values (@nexttransid, cast(getdate() as date), @cardnum, @amount, 4)
print 'Invalid Card Details'; end
end
go

exec withdraw '1324327436569', '1770', 1000