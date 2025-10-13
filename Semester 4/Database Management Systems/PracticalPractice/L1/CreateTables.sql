CREATE DATABASE MiniFacebook
USE MiniFacebook

CREATE TABLE Users(
	user_id INT PRIMARY KEY IDENTITY,
	user_name VARCHAR(50),
	user_city VARCHAR(50),
	user_dob DATE)

CREATE TABLE Categories(
	category_id INT PRIMARY KEY IDENTITY,
	category_description VARCHAR(50))

CREATE TABLE Pages(
	page_id INT PRIMARY KEY IDENTITY,
	page_name VARCHAR(50),
	category_id INT FOREIGN KEY REFERENCES Categories(category_id))

CREATE TABLE Likes(
	like_id INT PRIMARY KEY IDENTITY,
	user_id INT FOREIGN KEY REFERENCES Users(user_id),
	page_id INT FOREIGN KEY REFERENCES Pages(page_id),
	like_date DATE DEFAULT GETDATE())

CREATE TABLE Posts(
	post_id INT PRIMARY KEY IDENTITY,
	user_id INT FOREIGN KEY REFERENCES Users(user_id),
	post_date DATE DEFAULT GETDATE(),
	post_text VARCHAR(50),
	post_shares INT)

CREATE TABLE Comments(
	comment_id INT PRIMARY KEY IDENTITY,
	comment_text VARCHAR(50),
	comment_date DATE DEFAULT GETDATE(),
	comment_top BIT,
	post_id INT FOREIGN KEY REFERENCES Posts(post_id))

INSERT INTO Users(user_name, user_city, user_dob) VALUES ('user1', 'city1', '05-05-2000'), ('user2', 'city2', '02-02-2002'), ('user3', 'city3', '03-03-2003')
INSERT INTO Posts(user_id, post_text, post_shares) VALUES (1, 'text1', 1), (2, 'text2', 2), (3, 'text3', 3)