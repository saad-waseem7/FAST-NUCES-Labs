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

insert dbo.users (User_ID,UserName, Age, Country,privacy) values (1,N'Ali123', 18, N'Pakistan',1)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (2,N'Aliza', 40, N'USA',1)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (3,N'Aysha', 19, N'Iran',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (4,N'DonaldTrump', 60, N'USA',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (5,N'ImranKhan', 55, N'Pakistan',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (6,N'Natasha', 28, N'USA',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (7,N'Samuel', 37, N'Australia',0)
insert dbo.users (User_ID,UserName, Age, Country,privacy) values (8,N'Sara', 30, N'Iran',1)

create table Following
(
FollowerUserName varchar(20) Foreign key References Users(UserName) ,
FollowedUserName varchar(20) Foreign key References Users(UserName),
primary key (FollowerUserName, FollowedUserName)
)

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

Create table Tweets
(
TweetID int primary key,
UserName varchar(20) Foreign key References Users(UserName),
Text varchar(140)
)

insert dbo.Tweets (TweetID, UserName, Text) values (1, N'Ali123', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
insert dbo.Tweets (TweetID, UserName, Text) values (2, N'ImranKhan', N'Pakistan’s largest-ever population #Census  starts today in 63 districts after 19 years. ')
insert dbo.Tweets (TweetID, UserName, Text) values (3, N'Sara', N'Take the soldier who come to our door for #Census as A ThankYou from Pakistan Army for our devotion. #CensusWithSupportOfArmy')
insert dbo.Tweets (TweetID, UserName, Text) values (4, N'ImranKhan', N'Pakistan is ing to experience 6th #Census 2017.')
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

Create table Likes
(
TweetID int Foreign key References Tweets(TweetID),
LikeByUserName varchar(20) Foreign key References Users(UserName),
LikeOnDate date
primary key (TweetID ,LikeByUserName)
)

insert dbo.Likes (TweetID, LikeByUserName, LikeOnDate) values (1, N'Aliza', CAST(0x693C0B00 as Date))
insert dbo.Likes (TweetID, LikeByUserName, LikeOnDate) values (2, N'Aliza', CAST(0x693C0B00 as Date))

Create table Interests
(
InterestID int primary key,
Description varchar(30)
)

insert dbo.Interests (InterestID, Description) values (10, N'Politics')
insert dbo.Interests (InterestID, Description) values (11, N'Sports')
insert dbo.Interests (InterestID, Description) values (12, N'Movies')
insert dbo.Interests (InterestID, Description) values (13, N'Education')
insert dbo.Interests (InterestID, Description) values (14, N'Video Games')

create table UserInterests
(
UserName varchar(20)  Foreign key References Users(UserName),
InterestID int Foreign key References Interests(InterestID)
primary key (UserName, InterestID)
)

insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 10)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 11)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 13)
insert dbo.UserInterests (UserName, InterestID) values (N'Ali123', 14)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 10)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 11)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 13)
insert dbo.UserInterests (UserName, InterestID) values (N'Aliza', 14)
insert dbo.UserInterests (UserName, InterestID) values (N'ImranKhan', 10)
 
Create table Hashtags
(HashtagID int primary key,
Hashtag varchar(30))
 
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

-- Simple View: List of Users and Their Country
create view User_View as
select UserName, Country from Users;
select * from User_View;

-- Simple View: Tweets and Hashtags
create view Tweet_Hashtag as
select distinct t.Text, h.Hashtag from Tweets t
join Hashtags h on t.Text like '%' + h.Hashtag + '%';
select * from Tweet_Hashtag;

-- Nested View: Users and Their Followers Count
create view F_Count as 
select f.FollowedUserName, count(f.FollowerUserName) as Followers
from Following f
group by f.FollowedUserName;

create view F_Count_2 as 
select u.UserName, f.Followers from Users u
join F_Count f on u.UserName = f.FollowedUserName
where f.Followers > 1;

select * from F_Count_2;

-- Nested View: Users With Interests in Politics
create view Political_Interests as
select UserName from UserInterests
where InterestID = (select InterestID from Interests where Description = 'Politics');

select * from Political_Interests;

-- Insertion Using View: Add a New User
create view user_add as
select * from Users;

insert into Users (User_ID, UserName, Age, Country, Privacy)
values (9, 'Saad', 20, 'Germany', 1);

-- Deletion Using View: Remove a Tweet
create view del_tweet as
select * from Tweets;

delete from Tweets where TweetID = 1;

-- Insertion Using View: Add a Like
create view like_add as
select * from Likes;

insert into Likes (TweetID, LikeByUserName, LikeOnDate)
values (2, 'Saad', GETDATE());

-- Deletion Using View: Unfollow a User
create view del_follow as
select * from Following;

delete from Following where FollowerUserName = 'Ali123' and FollowedUserName = 'DonaldTrump';

-- Simple View: Users Who Have Liked Tweets
create view Liked_Tweets as
select distinct l.LikeByUserName, t.Text from Likes l
join Tweets t on l.TweetID = t.TweetID;

select * from Liked_Tweets;

-- Nested View: Most Liked Tweets
create view Like_Count as
select TweetID, count(LikeByUserName) as Likes
from Likes
group by TweetID;

create view Popular_Tweets as
select t.Text, lc.Likes from Tweets t
join Like_Count lc on t.TweetID = lc.TweetID
where lc.Likes > 1;

select * from Popular_Tweets;

-- Insertion Using View: Add a New Interest for a User
create view user_interest_add as
select * from UserInterests;

insert into UserInterests (UserName, InterestID)
values ('Saad', 10);
