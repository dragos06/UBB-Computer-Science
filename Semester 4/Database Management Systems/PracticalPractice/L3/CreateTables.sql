CREATE DATABASE ParkingLots

USE ParkingLots

CREATE TABLE Categories(
	c_id INT PRIMARY KEY IDENTITY,
	c_name VARCHAR(50))

CREATE TABLE Zones(
	z_id INT PRIMARY KEY IDENTITY,
	z_name VARCHAR(50))

CREATE TABLE Lots(
	l_id INT PRIMARY KEY IDENTITY,
	l_name VARCHAR(50),
	l_capacity INT,
	z_id INT FOREIGN KEY REFERENCES Zones(z_id),
	c_id INT FOREIGN KEY REFERENCES Categories(c_id))

CREATE TABLE Cars(
	c_id INT PRIMARY KEY IDENTITY,
	c_number VARCHAR(50))

CREATE TABLE Tickets(
	t_id INT PRIMARY KEY IDENTITY,
	p_id INT FOREIGN KEY REFERENCES Lots(l_id),
	c_id INT FOREIGN KEY REFERENCES Cars(c_id),
	t_arrival DATE DEFAULT GETDATE(),
	t_departure DATE)

INSERT INTO Zones(z_name) VALUES ('name1'), ('name2'), ('name3')
INSERT INTO Categories(c_name) VALUES ('cat1'), ('cat2'), ('cat3')
INSERT INTO Lots(l_name, l_capacity, z_id, c_id) VALUES ('lot1', 1, 1, 1), ('lot2', 2, 1, 2), ('lot3', 3, 2, 3)