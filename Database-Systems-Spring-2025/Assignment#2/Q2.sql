-- Create database Schema
USE master;
GO
CREATE DATABASE New;
GO
USE New

CREATE TABLE Users (
    userId NVARCHAR(50) NOT NULL,
    _password NVARCHAR(50),
    dob DATE,
    joinDate DATE,
    CONSTRAINT PK_USERS PRIMARY KEY (userId)
);

CREATE TABLE Followers (
    followee NVARCHAR(50) NOT NULL,
    follower NVARCHAR(50) NOT NULL,
    CONSTRAINT PK_FOLLOWERS PRIMARY KEY (followee, follower),
    CONSTRAINT FK_FOLLOWERS_FOLLOWEE FOREIGN KEY (followee) REFERENCES Users (userId),
    CONSTRAINT FK_FOLLOWERS_FOLLOWER FOREIGN KEY (follower) REFERENCES Users (userId)
);

CREATE TABLE QuestionCategories (
    category VARCHAR(40) NOT NULL,
    CONSTRAINT PK_QuestionCategories PRIMARY KEY (category)
);

CREATE TABLE Questions (
    questionId BIGINT NOT NULL,
    userId NVARCHAR(50) NOT NULL,
    _date DATE,
    category VARCHAR(40) NOT NULL,
    question NVARCHAR(200),
    CONSTRAINT PK_QUESTIONS PRIMARY KEY (questionId),
    CONSTRAINT FK_QUESTIONS_USERID FOREIGN KEY (userId) REFERENCES Users (userId),
    CONSTRAINT FK_QUESTIONS_CATEGORY FOREIGN KEY (category) REFERENCES QuestionCategories (category)
);

CREATE TABLE Answers (
    questionId BIGINT NOT NULL,
    userId NVARCHAR(50) NOT NULL,
    _date DATE,
    answer VARCHAR(500),
    CONSTRAINT PK_ANSWERS PRIMARY KEY (questionId, userId),
    CONSTRAINT FK_ANSWERS_QUESTIONID FOREIGN KEY (questionId) REFERENCES Questions (questionId),
    CONSTRAINT FK_ANSWERS_USERID FOREIGN KEY (userId) REFERENCES Users (userId)
);

-- Fixed incorrect date
INSERT INTO Users VALUES 
('ali', '123', '1992-11-11', '2008-04-05'),
('john', '12z3', '1995-11-30', '2009-10-10'),
('Junaid', '786q1', '1990-12-25', '2010-12-27'),
('peter', '1qwe52', '1992-12-25', '2010-05-23'),
('umer', '455errtw', '1989-11-15', '2007-12-12'); 

INSERT INTO Followers VALUES 
('ali', 'peter'),
('john', 'Junaid'), 
('john', 'peter'),
('junaid', 'john'), 
('peter', 'ali');

INSERT INTO QuestionCategories VALUES 
('International Relations'),
('Medical'),
('Programming'),
('Supernatural');

INSERT INTO Questions VALUES 
(1, 'peter', '2016-05-05', 'Medical', 'Will neurosurgeons be able to transplant head in the future?'),
(2, 'ali', '2017-01-31', 'Programming', 'Which language should I start from first: C++ or Java?'),
(3, 'peter', '2017-08-14', 'Supernatural', 'Are ghosts real?'),
(4, 'john', '2016-01-01', 'Medical', 'Does daily exercise decrease the risk of heart attack?'),
(5, 'peter', '2018-01-01', 'Programming', 'Can we make a foreign key using one attribute of a composite primary key?'),
(6, 'peter', '2019-01-01', 'International Relations', 'What are the pros and cons of Brexit for the UK?');

INSERT INTO Answers VALUES 
(1, 'ali', '2017-03-03', 'Head transplants are fake news.'),
(1, 'john', '2017-02-02', 'Probably. Much research is being carried out on this area.'),
(2, 'john', '2017-03-03', 'You should learn Java since Java is more popular than C++.'),
(2, 'umer', '2017-08-04', 'If you want to learn both, start with C++ first.'),
(3, 'ali', '2018-01-01', 'Scientifically, ghosts can neither be proved nor disproved.'),
(3, 'john', '2018-01-01', 'Yes, my grandmother saw one at midnight.'),
(3, 'junaid', '2018-03-01', 'Yes, they are real.'),
(4, 'peter', '2019-01-01', 'Exercise helps reduce the risk of heart disease.'),
(5, 'ali', '2018-01-02', 'A foreign key must include all attributes of a composite primary key.'),
(5, 'john', '2019-01-01', 'No, foreign keys must reference a unique or primary key.'),
(5, 'umer', '2019-02-14', 'You must make the complete primary key a foreign key.');


-- 1. Find users who have never asked a question
-- Part A: Using left join
select u.userId from Users u
left join Questions q on u.userId = q.userId
where q.userId is null;

-- Part B: Using not in with subquery
select userId from Users 
where userId not in (select userId from Questions);

-- 2. Find users who follow someone but are not followed back
-- Part A: Using left join
select f.follower from Followers f
left join Followers f2 on f.follower = f2.followee and f.followee = f2.follower
where f2.follower is null;

-- Part B: Using not exists with subquery
select follower from Followers 
where not exists (
    select 1 from Followers f2 where Followers.follower = f2.followee and Followers.followee = f2.follower
);

-- 3. Find users who have asked questions in at least 3 different categories
-- Part A: Using group by and having
select q.userId from Questions q
group by q.userId having count(distinct q.category) >= 3;

-- Part B: Using a subquery to count categories
select userId from Users 
where userId in (
    select userId from Questions group by userId having count(distinct category) >= 3
);

-- 4. Find the latest question asked in each category
-- Part A: Using left join
select q1.questionId, q1.category, q1.question, q1._date from Questions q1
left join Questions q2 on q1.category = q2.category and q1._date < q2._date
where q2.questionId is null;

-- Part B: Using a subquery
select questionId, category, question, _date from Questions 
where _date = (
    select max(_date) from Questions q2 where q2.category = Questions.category
);

-- 5. Find users who have asked questions in all categories
-- Part A: Using join and group by
select q.userId from Questions q
group by q.userId having count(distinct q.category) = (select count(*) from QuestionCategories);

-- Part B: Using a subquery
select userId from Users 
where userId in (
    select userId from Questions group by userId having count(distinct category) = (select count(*) from QuestionCategories)
);

-- 6. Find users who have both asked and answered at least one question
-- Part A: Using INNER join
select distinct q.userId from Questions q
join Answers a on q.userId = a.userId;

-- Part B: Using subqueries
select userId from Users 
where userId in (select userId from Questions) 
and userId in (select userId from Answers);

-- 7. Get the user with the highest number of followers
-- Part A: Using group by and order by
select top 1 f.followee, count(f.follower) AS follower_count from Followers f
group by f.followee order by follower_count desc;

-- Part B: Using a subquery
select followee from Followers group by followee 
having count(follower) = (
    select max(follower_count) from (select count(follower) AS follower_count from Followers group by followee) AS temp
);

-- 8. List questions with the number of answers, sorted in descending order
-- Part A: Using left join and count
select q.questionId, q.question, count(a.userId) AS answer_count from Questions q
left join Answers a on q.questionId = a.questionId
group by q.questionId, q.question order by answer_count desc;

-- Part B: Using a subquery
select questionId, question, 
    (select count(*) from Answers a where a.questionId = q.questionId) AS answer_count 
from Questions q order by answer_count desc;

-- 9. Find questions where the asker follows an answerer
-- Part A: Using join
select distinct q.questionId, q.question from Questions q
join Answers a on q.questionId = a.questionId
join Followers f on q.userId = f.follower and a.userId = f.followee;

-- Part B: Using a subquery
select questionId, question from Questions 
where questionId in (
    select distinct a.questionId from Answers a 
    where a.userId in (
        select followee from Followers where follower = (select userId from Questions where questionId = a.questionId)
    )
);

-- 10. Find users who have both asked and answered questions
-- Part A: Using INNER join
select distinct q.userId from Questions q
join Answers a on q.userId = a.userId;

-- Part B: Using subqueries
select userId from Users 
where userId in (select userId from Questions) and userId in (select userId from Answers);

-- 11. Find the most answered question
-- Part A: Using group by and order by
select top 1 q.questionId, q.question, count(a.userId) AS answer_count 
from Questions q join Answers a on q.questionId = a.questionId
group by q.questionId, q.question order by answer_count desc;

-- Part B: Using a subquery
select questionId, question from Questions 
where questionId = (
    select top 1 questionId from Answers group by questionId order by count(*) desc
);

-- 12. Find users who only answered questions in categories they never asked questions in
-- Part A: Using join and not exists
select distinct a.userId from Answers a
join Questions q on a.questionId = q.questionId
where not exists (
    select 1 from Questions q2 where q2.userId = a.userId and q2.category = q.category
);

-- Part B: Using subqueries
select distinct userId from Answers 
where userId not in (
    select distinct userId from Questions where category in (
        select distinct category from Answers a join Questions q on a.questionId = q.questionId
    )
);

-- 13. Get users and the number of unique users they follow
-- Part A: Using count and group by
select f.follower, count(distinct f.followee) AS following_count from Followers f group by f.follower;

-- Part B: Using a subquery
select userId, 
    (select count(distinct followee) from Followers where follower = u.userId) AS following_count from Users u;
