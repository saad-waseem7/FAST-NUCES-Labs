-- Create database Schema
USE master;
GO
CREATE DATABASE twitter;
GO
USE twitter

create table Users (
    User_ID int,
    UserName varchar(20) primary key,
    Age int,
    Country varchar(20),
    privacy int
);

insert dbo.users (User_ID,UserName, Age, Country,privacy) values (1,N'Ali123', 18, N'Pakistan',1)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (2,N'Aliza', 40, N'USA',1)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (3,N'Aysha', 19, N'Iran',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (4,N'DonaldTrump', 60, N'USA',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (5,N'ImranKhan', 55, N'Pakistan',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (6,N'Natasha', 28, N'USA',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (7,N'Samuel', 37, N'Australia',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (8,N'Sara', 30, N'Iran',1)

create table Following (
    FollowerUserName varchar(20) Foreign key References Users(UserName),
    FollowedUserName varchar(20) Foreign key References Users(UserName),
    primary key (FollowerUserName, FollowedUserName)
);

insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Ali123', N'DonaldTrump')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Aliza', N'Ali123')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Aliza', N'DonaldTrump')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Aliza', N'ImranKhan')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Aysha', N'ImranKhan')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'DonaldTrump', N'ImranKhan')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'ImranKhan', N'DonaldTrump')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Natasha', N'ImranKhan')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Samuel', N'DonaldTrump')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Samuel', N'ImranKhan')
insert dbo.Following (FollowerUserName, FollowedUserName) values (N'Sara', N'DonaldTrump')

Create table Tweets (
    TweetID int primary key,
    UserName varchar(20) Foreign key References Users(UserName),
    Text varchar(140)
);

insert dbo.Tweets (TweetID, UserName, Text) values (1, N'Ali123', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
insert dbo.Tweets (TweetID, UserName, Text) values (2, N'ImranKhan', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
insert dbo.Tweets (TweetID, UserName, Text) values (3, N'Sara', N'Take the soldier who come to our door for #Census as A ThankYou from Pakistan Army for our devotion. #CensusWithSupportOfArmy')
insert dbo.Tweets (TweetID, UserName, Text) values (4, N'ImranKhan', N'Pakistan is going to experience 6th #Census 2017.')
insert dbo.Tweets (TweetID, UserName, Text) values (5, N'Sara', N'Only #census can reveal where this aunty lives ')
insert dbo.Tweets (TweetID, UserName, Text) values (6, N'ImranKhan', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
insert dbo.Tweets (TweetID, UserName, Text) values (7, N'Sara', N'Over 1 million decrypted Gmail and Yahoo accounts allegedly up for sale on the Dark Web https://geekz0ne.fr/shaarli/?wQRSoQ  #piratage')
insert dbo.Tweets (TweetID, UserName, Text) values (8, N'Sara', N'Harry pot-head and the Sorcerer''s stoned')
insert dbo.Tweets (TweetID, UserName, Text) values (9, N'DonaldTrump', N'LSDespicable Me  #DrugMovies')
insert dbo.Tweets (TweetID, UserName, Text) values (10, N'ImranKhan', N'Forrest Bump #DrugMovies @midnight')
insert dbo.Tweets (TweetID, UserName, Text) values (12, N'DonaldTrump', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
insert dbo.Tweets (TweetID, UserName, Text) values (13, N'Sara', N'#DrugMovies')
insert dbo.Tweets (TweetID, UserName, Text) values (14, N'DonaldTrump', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')
insert dbo.Tweets (TweetID, UserName, Text) values (15, N'Aliza', N'Quand tu te lèves 3h en avance (littéralement) pour la #massecritique ')

Create table Likes (
    TweetID int Foreign key References Tweets(TweetID),
    LikeByUserName varchar(20) Foreign key References Users(UserName),
    LikeOnDate date primary key (TweetID, LikeByUserName)
);

insert dbo.Likes (TweetID, LikeByUserName, LikeOnDate) values (1, N'Aliza', CAST(0x693C0B00 AS Date))
insert dbo.Likes (TweetID, LikeByUserName, LikeOnDate) values (2, N'Aliza', CAST(0x693C0B00 AS Date))

Create table Interests (
    InterestID int primary key,
    Description varchar(30)
);

insert dbo.Interests (InterestID, Description) values (10, N'Politics')
insert dbo.Interests (InterestID, Description) values (11, N'Sports')
insert dbo.Interests (InterestID, Description) values (12, N'Movies')
insert dbo.Interests (InterestID, Description) values (13, N'Education')
insert dbo.Interests (InterestID, Description) values (14, N'Video Games')

create table UserInterests
(UserName varchar(20)  Foreign key References Users(UserName),
InterestID int Foreign key References Interests(InterestID)
primary key (UserName, InterestID)
);

insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 10)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 11)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 13)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 14)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 10)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 11)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 13)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 14)
insert dbo.UserInterests (UserName, InterestID) values (N'ImranKhan', 10)

Create table Hashtags (HashtagID int primary key, Hashtag varchar(30));
 
insert dbo.Hashtags (HashtagID, Hashtag) values (1, N'#Census')
insert dbo.Hashtags (HashtagID, Hashtag) values (2, N'#ClassiqueMatin')
insert dbo.Hashtags (HashtagID, Hashtag) values (3, N'#MasseCritique')
insert dbo.Hashtags (HashtagID, Hashtag) values (4, N'#piratage')
insert dbo.Hashtags (HashtagID, Hashtag) values (5, N'#DrugMovies')

Select * from Following
Select * from Hashtags
Select * from Interests
Select * from Tweets
Select * from UserInterests
Select * from Users

-- 1. Find Maximum, Minimum, Average, and Standard Deviation of User Ages
select max(Age) as _Max, min(Age) as _Min, avg(Age) as _Avg, stdev(Age) as StdDev
from Users;

-- 2. Find the User with the Most Followers
select Top 1 FollowedUserName from Following
group by FollowedUserName order by count(*) desc;

-- 4. Users Who Have Never Tweeted
select UserName from Users
where UserName not in (select distinct UserName from Tweets);

-- 5. Find Hashtags Used by Each User and How Many Times They Used Them
select t.UserName, h.Hashtag, count(*) as count from Tweets t
join Hashtags h on t.Text like '%' + h.Hashtag + '%'
group by t.UserName, h.Hashtag;

-- 6. Find Users Who Have Never Used the Hashtag #Census
select UserName from Users
where UserName not in (select distinct UserName from Tweets where Text like '%#Census%');

-- 7. Users Who Have Never Been Followed (Using EXCEPT)
select UserName from Users
except select FollowedUserName from Following;

-- 8. Users Who Have Never Been Followed (Using NOT EXISTS)
select UserName from Users u
where not exists (select 1 from Following f where f.FollowedUserName = u.UserName);

-- 10. Total Tweets Per Country (Ordered by Country Name)
select u.Country, count(t.TweetID) as Total from Users u
left join Tweets t on u.UserName = t.UserName
group by u.Country order by u.Country;

-- 12. Users Who Have At Least One Follower from Pakistan
select distinct f.FollowedUserName from Following f
join Users u on f.FollowerUserName = u.UserName where u.Country = 'Pakistan';

-- 13. Interest with the Most Users
select top 1 u.InterestID, Description, count(UserName) as Total from UserInterests as u
join Interests on u.InterestID = Interests.InterestID
group by u.InterestID, Description order by Total desc;
