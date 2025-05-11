-- Create database Schema
USE master;
GO
CREATE DATABASE DB123;
GO
USE DB123

create table _User(
userId int primary key,
name varchar(20) not null,
phoneNum varchar(15) not null,
city varchar(20) not null
);

create table CardType(
cardTypeID int primary key,
name varchar(15),
description varchar(40) null
);

create Table Card(
cardNum Varchar(20) primary key,
cardTypeID int foreign key references CardType(cardTypeID),
PIN varchar(4) not null,
expireDate date not null,
balance float not null
);

Create table UserCard(
userID int foreign key references _User(userId),
cardNum varchar(20) foreign key references Card(cardNum),
primary key(cardNum)
);

create table Transactions(
transId int primary key,
transDate date not null,
cardNum varchar(20) foreign key references Card(cardNum),
amount int not null
);

INSERT dbo._User (userId, name, phoneNum, city) VALUES (1, N'Ali', N'03036067000', N'Narowal');
INSERT dbo._User (userId, name, phoneNum, city) VALUES (2, N'Ahmed', N'03036047000', N'Lahore');
INSERT dbo._User (userId, name, phoneNum, city) VALUES (3, N'Aqeel', N'03036063000', N'Karachi');
INSERT dbo._User (userId, name, phoneNum, city) VALUES (4, N'Usman', N'03036062000', N'Sialkot');
INSERT dbo._User (userId, name, phoneNum, city) VALUES (5, N'Hafeez', N'03036061000', N'Lahore');

INSERT dbo.CardType (cardTypeID, name, description) VALUES (1, N'Debit', N'Spend Now, Pay Now');
INSERT dbo.CardType (cardTypeID, name, description) VALUES (2, N'Credit', N'Spend Now, Pay later');

INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1234', 1, N'1770', CAST(N'2022-07-01' AS Date), 43025.31);
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1235', 1, N'9234', CAST(N'2020-03-02' AS Date), 14425.62);
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1236', 1, N'1234', CAST(N'2019-02-06' AS Date), 34325.52);
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1237', 2, N'1200', CAST(N'2021-02-05' AS Date), 24325.3);
INSERT dbo.Card (cardNum, cardTypeID, PIN, expireDate, balance) VALUES (N'1238', 2, N'9004', CAST(N'2020-09-02' AS Date), 34025.12);

INSERT dbo.UserCard (userID, cardNum) VALUES (1, N'1234');
INSERT dbo.UserCard (userID, cardNum) VALUES (1, N'1235');
INSERT dbo.UserCard (userID, cardNum) VALUES (2, N'1236');
INSERT dbo.UserCard (userID, cardNum) VALUES (3, N'1238');
Insert dbo.UserCard (userID, cardNum) VALUES (4, N'1237');

INSERT dbo.Transactions (transId, transDate, cardNum, amount) VALUES (1, CAST(N'2017-02-02' AS Date), N'1234', 500);
INSERT dbo.Transactions (transId, transDate, cardNum, amount) VALUES (2, CAST(N'2018-02-03' AS Date), N'1235', 3000);
INSERT dbo.Transactions (transId, transDate, cardNum, amount) VALUES (3, CAST(N'2020-01-06' AS Date), N'1236', 2500);
INSERT dbo.Transactions (transId, transDate, cardNum, amount) VALUES (4, CAST(N'2016-09-09' AS Date), N'1238', 2000);
INSERT dbo.Transactions (transId, transDate, cardNum, amount) VALUES (5, CAST(N'2020-02-10' AS Date), N'1234', 6000);

select * from _User
select * from UserCard
select * from Card
select * from CardType
select * from Transactions

-- 1. count of unique users for each Card type
select ct.name as card_type, count(distinct uc.userid) as unique_users  
from UserCard uc  
inner join Card c on uc.cardnum = c.cardnum  
inner join CardType ct on c.cardtypeid = ct.cardtypeid  
group by ct.name;

-- 2. Card numbers and user names with balance between 2000 and 4000
select c.cardnum, u.name as user_name from Card c  
inner join UserCard uc on c.cardnum = uc.cardnum  
inner join _User u on uc.userid = u.userid  
where c.balance > 2000 and c.balance < 4000;

-- 3. users without a Card
-- (a) using except
select name from _User except select u.name from _User u  
inner join UserCard uc on u.userid = uc.userid;

-- (b) using left join
select u.name from _User u  
left join UserCard uc on u.userid = uc.userid  
where uc.cardnum is null;

-- 5. count of cards per Card type where total Transactions exceed 6000 (2015-2017)
select ct.name as card_type, count(distinct c.cardnum) as total_cards from Card c  
inner join CardType ct on c.cardtypeid = ct.cardtypeid  
inner join Transactions t on c.cardnum = t.cardnum  
where t.transdate between '2015-01-01' and '2017-12-31' group by ct.name having sum(t.amount) > 6000;

-- 6. users with cards expiring in the next 3 months
select u.*, ct.name as card_type from _User u  
inner join UserCard uc on u.userid = uc.userid  
inner join Card c on uc.cardnum = c.cardnum  
inner join CardType ct on c.cardtypeid = ct.cardtypeid  
where c.expiredate between getdate() and dateadd(month, 3, getdate());

-- 7. users whose total balance is at least 5000
select u.userid, u.name from _User u  
inner join UserCard uc on u.userid = uc.userid  
inner join Card c on uc.cardnum = c.cardnum  
group by u.userid, u.name having sum(c.balance) >= 5000;

-- 8. Card pairs expiring in the same year
select c1.cardnum, c2.cardnum, year(c1.expiredate) as expiry_year from Card c1  
inner join Card c2 on c1.cardnum < c2.cardnum where year(c1.expiredate) = year(c2.expiredate);

-- 9. users with names starting with the same letter
select u1.name, u2.name from _User u1  
inner join _User u2 on left(u1.name, 1) = left(u2.name, 1) where u1.userid < u2.userid;

-- 10. users who have both a credit Card and a debit Card
select u.userid, u.name from _User u  
inner join UserCard uc on u.userid = uc.userid  
inner join Card c on uc.cardnum = c.cardnum  
inner join CardType ct on c.cardtypeid = ct.cardtypeid  
where ct.name in ('credit', 'debit') group by u.userid, u.name having count(distinct ct.name) = 2;

-- 11. city-wise user count and total transaction sum
select u.city, count(distinct u.userid) as user_count, sum(t.amount) as total_transaction from _User u  
inner join UserCard uc on u.userid = uc.userid  
inner join Card c on uc.cardnum = c.cardnum  
inner join Transactions t on c.cardnum = t.cardnum group by u.city;