-- Create database Schema
USE master;
GO
CREATE DATABASE ATM;
GO
USE ATM

create table _User(
userId int primary key,
name varchar(20) not null,
phoneNum varchar(15) not null,
city varchar(20) not null
)

create table CardType(
cardTypeID int primary key,
name varchar(15),
description varchar(40) null
)

create Table Card(
cardNum Varchar(20) primary key,
cardTypeID int foreign key references  CardType(cardTypeID),
PIN varchar(4) not null,
expireDate date not null,
balance float not null
)

Create table UserCard(
userID int foreign key references _User(userId),
cardNum varchar(20) foreign key references Card(cardNum),
primary key(cardNum)
)

create table _Transaction(
transId int primary key,
transDate date not null,
cardNum varchar(20) foreign key references Card(cardNum),
amount int not null
)


INSERT dbo._User (userId, name, phoneNum, city) VALUES (1, N'Ali', N'03036067000', N'Narowal')
INSERT dbo._User (userId, name, phoneNum, city) VALUES (2, N'Ahmed', N'03036047000', N'Lahore')
INSERT dbo._User (userId, name, phoneNum, city) VALUES (3, N'Aqeel', N'03036063000', N'Karachi')
INSERT dbo._User (userId, name, phoneNum, city) VALUES (4, N'Usman', N'03036062000', N'Sialkot')
INSERT dbo._User (userId, name, phoneNum, city) VALUES (5, N'Hafeez', N'03036061000', N'Lahore')

INSERT dbo.CardType (cardTypeID, name, description) VALUES (1, N'Debit', N'Spend Now, Pay Now')
INSERT dbo.CardType (cardTypeID, name, description) VALUES (2, N'Credit', N'Spend Now, Pay later')

INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1234', 1, N'1770', CAST(N'2022-07-01' AS Date), 43025.31)
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1235', 1, N'9234', CAST(N'2020-03-02' AS Date), 14425.62)
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1236', 1, N'1234', CAST(N'2019-02-06' AS Date), 34325.52)
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1237', 2, N'1200', CAST(N'2021-02-05' AS Date), 24325.3)
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1238', 2, N'9004', CAST(N'2020-09-02' AS Date), 34025.12)

INSERT dbo.UserCard (userID, cardNum) VALUES (1, N'1234')
INSERT dbo.UserCard (userID, cardNum) VALUES (1, N'1235')
INSERT dbo.UserCard (userID, cardNum) VALUES (2, N'1236')
INSERT dbo.UserCard (userID, cardNum) VALUES (3, N'1238')
Insert  dbo.UserCard (userID, cardNum) VALUES (4, N'1237')

INSERT dbo._Transaction (transId, transDate, cardNum, amount) VALUES (1, CAST(N'2017-02-02' AS Date), N'1234', 500)
INSERT dbo._Transaction (transId, transDate, cardNum, amount) VALUES (2, CAST(N'2018-02-03' AS Date), N'1235', 3000)
INSERT dbo._Transaction (transId, transDate, cardNum, amount) VALUES (3, CAST(N'2020-01-06' AS Date), N'1236', 2500)
INSERT dbo._Transaction (transId, transDate, cardNum, amount) VALUES (4, CAST(N'2016-09-09' AS Date), N'1238', 2000)
INSERT dbo._Transaction (transId, transDate, cardNum, amount) VALUES (5, CAST(N'2020-02-10' AS Date), N'1234', 6000)

Select * from _User
Select * from UserCard
Select * from Card
Select * from CardType
Select * from _Transaction

-- Retrieve the user name, card number, and balance for all users who own a card.
select U.* from _User U
inner join UserCard UC on U.userId = UC.userID inner join Card C on UC.cardNum = C.cardNum;

--Retrieve transaction details along with the user name who performed the transaction.
select T.*,U.name from _Transaction T
inner join Card C on T.cardNum = C.cardNum
inner join UserCard UC on C.cardNum = UC.cardNum
inner join _User U on UC.userID = U.userId;

-- Get all possible combinations of users and card types.
select U.userId, U.name, CT.cardTypeID, CT.name from _User U cross join CardType CT;

--Retrieve all users and their associated card details (if they have any).
select U.*,C.cardNum,CT.name,C.PIN,C.expireDate,C.balance from _User U
left join UserCard UC on U.userId = UC.userID
left join Card C on UC.cardNum = C.cardNum
left join CardType CT on C.cardTypeID = CT.cardTypeID;

-- Retrieve all cards along with their transaction details (even if no transaction has occurred).
select C.*,CT.name,T.* from Card C
inner join CardType CT on C.cardTypeID = CT.cardTypeID left join _Transaction T on C.cardNum = T.cardNum;

-- Retrieve transaction details along with user information (even if the user details are missing).
select T.*,U.* from _Transaction T left join UserCard UC on T.cardNum = UC.cardNum left join _User U on UC.userID = U.userId;

-- Retrieve all card types and associated card details (even if no card is issued).
select CT.*,C.* from CardType CT left join Card C on CT.cardTypeID = C.cardTypeID;

-- Retrieve card numbers that have both transactions and are assigned to users.
select C.cardNum,U.userId,U.name,T.transId,T.amount from UserCard UC
inner join _User U on UC.userID = U.userId
inner join Card C on UC.cardNum = C.cardNum
inner join _Transaction T on C.cardNum = T.cardNum;

-- Retrieve all card numbers that have not been used in any transactions.
select C.cardNum from Card C where C.cardNum not in (select T.cardNum from _Transaction T);

-- Retrieve all transactions where the user's name contains the letter 'e' and the transaction amount is greater than 2000.
select U.*, T.* from _User U
inner join UserCard UC on U.userId = UC.userID
inner join Card C on UC.cardNum = C.cardNum
inner join _Transaction T on C.cardNum = T.cardNum
where U.name like '%e%' and T.amount > 2000;

-- Retrieve all card numbers and their balance, but only include cards with a balance greater than 30,000.
select C.cardNum,C.balance from Card C where C.balance > 30000;

-- Generate a list of all possible user-card type combinations where the user is from Lahore
select U.userId,U.name,CT.cardTypeID,CT.name from _User U cross join CardType CT where U.city = 'Lahore';

--Retrieve all transactions that happened in the year 2020, along with the user's name and card number.
select T.transId,T.transDate,U.name,C.cardNum from _Transaction T
inner join Card C on T.cardNum = C.cardNum
inner join UserCard UC on C.cardNum = UC.cardNum
inner join _User U on UC.userID = U.userId
where year(T.transDate) = 2020;
