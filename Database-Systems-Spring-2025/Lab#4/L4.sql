-- Create database Schema
USE master;
GO
CREATE DATABASE twitter;
GO
USE twitter

create table Users
(
User_ID int,
UserName varchar(20) primary key,
Age int,
Country varchar(20),
privacy int
)

INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (1,N'Ali123', 18, N'Pakistan',1)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (2,N'Aliza', 40, N'USA',1)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (3,N'Aysha', 19, N'Iran',0)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (4,N'DonaldTrump', 60, N'USA',0)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (5,N'ImranKhan', 55, N'Pakistan',0)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (6,N'Natasha', 28, N'USA',0)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (7,N'Samuel', 37, N'Australia',0)
INSERT dbo.users (User_ID,UserName, Age, Country,privacy) VALUES (8,N'Sara', 30, N'Iran',1)

create table Following
(
FollowerUserName varchar(20) Foreign key References Users(UserName) ,
FollowedUserName varchar(20) Foreign key References Users(UserName),
primary key (FollowerUserName, FollowedUserName)
)

INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Ali123', N'DonaldTrump')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Aliza', N'Ali123')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Aliza', N'DonaldTrump')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Aliza', N'ImranKhan')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Aysha', N'ImranKhan')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'DonaldTrump', N'ImranKhan')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'ImranKhan', N'DonaldTrump')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Natasha', N'ImranKhan')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Samuel', N'DonaldTrump')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Samuel', N'ImranKhan')
INSERT dbo.Following (FollowerUserName, FollowedUserName) VALUES (N'Sara', N'DonaldTrump')

Create table Tweets
(
TweetID int primary key,
UserName varchar(20) Foreign key References Users(UserName),
Text varchar(140)
)

INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (1, N'Ali123', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (2, N'ImranKhan', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (3, N'Sara', N'Take the soldier who come to our door for #Census as A ThankYou from Pakistan Army for our devotion. #CensusWithSupportOfArmy')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (4, N'ImranKhan', N'Pakistan is ing to experience 6th #Census 2017.')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (5, N'Sara', N'Only #census can reveal where this aunty lives ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (6, N'ImranKhan', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (7, N'Sara', N'Over 1 million decrypted Gmail and Yahoo accounts allegedly up for sale on the Dark Web https://geekz0ne.fr/shaarli/?wQRSoQ  #piratage')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (8, N'Sara', N'Harry pot-head and the Sorcerer''s stoned')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (9, N'DonaldTrump', N'LSDespicable Me  #DrugMovies')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (10, N'ImranKhan', N'Forrest Bump #DrugMovies @midnight')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (12, N'DonaldTrump', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (13, N'Sara', N'#DrugMovies')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (14, N'DonaldTrump', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
INSERT dbo.Tweets (TweetID, UserName, Text) VALUES (15, N'Aliza', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')

Create table Likes
(
TweetID int Foreign key References Tweets(TweetID),
LikeByUserName varchar(20) Foreign key References Users(UserName),
LikeOnDate date
primary key (TweetID ,LikeByUserName)
)

INSERT dbo.Likes (TweetID, LikeByUserName, LikeOnDate) VALUES (1, N'Aliza', CAST(0x693C0B00 AS Date))
INSERT dbo.Likes (TweetID, LikeByUserName, LikeOnDate) VALUES (2, N'Aliza', CAST(0x693C0B00 AS Date))

Create table Interests
(
InterestID int primary key,
Description varchar(30)
)

INSERT dbo.Interests (InterestID, Description) VALUES (10, N'Politics')
INSERT dbo.Interests (InterestID, Description) VALUES (11, N'Sports')
INSERT dbo.Interests (InterestID, Description) VALUES (12, N'Movies')
INSERT dbo.Interests (InterestID, Description) VALUES (13, N'Education')
INSERT dbo.Interests (InterestID, Description) VALUES (14, N'Video Games')

create table UserInterests
(UserName varchar(20)  Foreign key References Users(UserName),
InterestID int Foreign key References Interests(InterestID)
primary key (UserName, InterestID)
)
 
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Ali123', 10)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Ali123', 11)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Ali123', 13)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Ali123', 14)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Aliza', 10)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Aliza', 11)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Aliza', 13)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'Aliza', 14)
INSERT dbo.UserInterests (UserName, InterestID) VALUES (N'ImranKhan', 10)

Create table Hashtags
(HashtagID int primary key,
Hashtag varchar(30))
 
INSERT dbo.Hashtags (HashtagID, Hashtag) VALUES (1, N'#Census')
INSERT dbo.Hashtags (HashtagID, Hashtag) VALUES (2, N'#ClassiqueMatin')
INSERT dbo.Hashtags (HashtagID, Hashtag) VALUES (3, N'#MasseCritique')
INSERT dbo.Hashtags (HashtagID, Hashtag) VALUES (4, N'#piratage')
INSERT dbo.Hashtags (HashtagID, Hashtag) VALUES (5, N'#DrugMovies')

Select * from Following
Select * from Hashtags
Select * from Interests
Select * from Tweets
Select * from UserInterests
Select * from Users

--1. Retrieve users who follow someone who follows "ImranKhan"
select distinct f1.FollowerUserName from Following f1 
where f1.FollowerUserName in (select f2.FollowerUserName from Following f2 
where f2.FollowedUserName = 'ImranKhan')

--2. Get all tweets liked by users who follow "DonaldTrump"
select t.* from Tweets t join Likes l on t.TweetID = l.TweetID 
join Following f on l.LikeByUserName = f.FollowerUserName 
where f.FollowedUserName = 'DonaldTrump';

--3. Find users who have at least one common interest with "Ali123"
select distinct u1.username from UserInterests u1
where u1.InterestID in (select u2.InterestID from UserInterests u2
where u2.UserName='Ali123') and u1.UserName!='Ali123'

--4. Retrieve all tweets that contain at least one hashtag
select t.* from Tweets t join Hashtags h on t.TweetID = h.HashtagID;

--5. Find users who have liked tweets that contain the hashtag "#Census"
select l.LikeByUserName from Likes l join Tweets t on l.TweetID = t.TweetID 
join Hashtags h on t.TweetID = h.HashtagID 
where h.Hashtag = '#Census';

--6. Retrieve users who follow at least one user from the USA
select distinct f.FollowerUserName from Following f 
join Users u on f.FollowedUserName = u.UserName where u.Country = 'USA';

--7. Retrieve tweets by users who have at least one interest in "Politics"
select t.* from Tweets t join Users u on t.UserName = u.UserName 
join UserInterests ui on u.UserName = ui.UserName 
join Interests i on ui.InterestID = i.InterestID where i.Description = 'Politics';
