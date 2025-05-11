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

-- 8. Find tweets that are liked by users who also follow "Sara"
select distinct l.TweetID, t.Text from Likes l
join Following f on l.LikeByUserName = f.FollowerUserName
join Tweets t on l.TweetID = t.TweetID
where f.FollowedUserName = 'Sara';

-- 9. Retrieve users who follow someone that follows them back
select f1.FollowerUserName, f1.FollowedUserName from Following f1
join Following f2 on f1.FollowerUserName = f2.FollowedUserName 
and f1.FollowedUserName = f2.FollowerUserName;

-- 10. Find tweets posted by users who have liked tweets from "DonaldTrump"
Select distinct t.* from Tweets t
inner join Likes l on t.UserName = l.LikeByUserName
inner join Tweets tt on l.TweetID = tt.TweetID
where tt.UserName = 'DonaldTrump'

-- 11. Retrieve tweets that are both liked and retweeted (if a Retweets table existed)
select distinct l.TweetID, t.Text from Likes l
join Tweets t on l.TweetID = t.TweetID;

-- 12. Find users who have never tweeted
select u.UserName from Users u
left join Tweets t on u.UserName = t.UserName
where t.TweetID is null;

-- 13. Get all users who like the same tweets as "Ali123"
select distinct l1.LikeByUserName from Likes l1
join Likes l2 on l1.TweetID = l2.TweetID
where l2.LikeByUserName = 'Ali123' and l1.LikeByUserName <> 'Ali123';

-- 15. Find users who have liked tweets from users they don’t follow
select distinct l.LikeByUserName from Likes l
join Tweets t on l.TweetID = t.TweetID
where not exists (select 1 from Following f where f.FollowerUserName = l.LikeByUserName 
    and f.FollowedUserName = t.UserName
);
