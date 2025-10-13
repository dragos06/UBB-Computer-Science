CREATE DATABASE SmartHomes
USE SmartHomes

CREATE TABLE Neighborhoods(
	n_id INT PRIMARY KEY IDENTITY,
	n_name VARCHAR(50),
	n_location VARCHAR(50))

CREATE TABLE Residents(
	r_id INT PRIMARY KEY IDENTITY,
	r_name VARCHAR(50),
	r_phone VARCHAR(10))

CREATE TABLE Homes(
	h_id INT PRIMARY KEY IDENTITY,
	h_name VARCHAR(50),
	h_address VARCHAR(50),
	n_id INT FOREIGN KEY REFERENCES Neighborhoods(n_id),
	r_id INT FOREIGN KEY REFERENCES Residents(r_id))

CREATE TABLE Devices(
	d_id INT PRIMARY KEY IDENTITY,
	d_name VARCHAR(50))

CREATE TABLE HomesDevices(
	hd_id INT PRIMARY KEY IDENTITY,
	h_id INT FOREIGN KEY REFERENCES Homes(h_id),
	d_id INT FOREIGN KEY REFERENCES Devices(d_id))

INSERT INTO Neighborhoods (n_name, n_location) VALUES ('n1', 'loc1'), ('n2', 'loc2'), ('n3', 'loc3')
INSERT INTO Residents (r_name, r_phone) VALUES ('r1', '1'), ('r2', '2')
INSERT INTO Homes (h_name, h_address, n_id, r_id) VALUES ('h1', 'a1', 1, 1), ('h2', 'a2', 2, 1), ('h3', 'a3', 2, 2)