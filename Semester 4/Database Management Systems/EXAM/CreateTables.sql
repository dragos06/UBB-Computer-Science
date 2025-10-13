CREATE DATABASE CulturalEvents

USE CulturalEvents

CREATE TABLE Buildings(
	b_id INT PRIMARY KEY IDENTITY,
	b_name VARCHAR(50),
	b_spaces INT,
	b_website VARCHAR(50))

CREATE TABLE Categories(
	c_id INT PRIMARY KEY IDENTITY,
	c_name VARCHAR(50),
	c_description VARCHAR(50))

CREATE TABLE CulEvents(
	ce_id INT PRIMARY KEY IDENTITY,
	ce_name VARCHAR(50),
	ce_resume VARCHAR(50),
	c_id INT FOREIGN KEY REFERENCES Categories(c_id))

CREATE TABLE Housings(
	h_id INT PRIMARY KEY,
	ce_id INT FOREIGN KEY REFERENCES CulEvents(ce_id),
	b_id INT FOREIGN KEY REFERENCES Buildings(b_id),
	h_start DATE,
	h_end DATE)

CREATE TABLE Subscribers(
	s_id INT PRIMARY KEY IDENTITY,
	s_name VARCHAR(50),
	ce_id INT FOREIGN KEY REFERENCES CulEvents(ce_id))

CREATE TABLE Tickets(
	s_id INT PRIMARY KEY FOREIGN KEY REFERENCES Subscribers(s_id),
	t_attendance DATETIME)

DROP TABLE Subscribers

INSERT INTO Categories (c_name, c_description) VALUES ('cat1', 'desc1'), ('cat2', 'desc2'), ('cat3', 'desc3')
INSERT INTO CulEvents (ce_name, ce_resume, c_id) VALUES ('event1', 'res1', 1), ('event2', 'res2', 2), ('event3', 'res3', 2)

SELECT * FROM Categories
SELECT * FROM CulEvents