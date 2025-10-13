USE SkiResort

EXEC dbo.InsertReservationWithRecovery
    @skier_fname = 'John',
    @skier_lname = 'Doe',
    @skier_skill = 'beginner',
    @housing_name = 'Snow Hut',
    @housing_location = 'South Ridge',
    @housing_type = 'Cabin',
    @housing_capacity = 4;

SELECT * FROM Reservations
SELECT * FROM ActionLog
DELETE FROM ActionLog
DELETE Reservations
DELETE Housings

EXEC dbo.InsertReservationWithRecovery
    @skier_fname = 'Jane',
    @skier_lname = 'Smith',
    @skier_skill = 'expert',  -- Invalid value
    @housing_name = 'Ice Den',
    @housing_location = 'North Point',
    @housing_type = 'Restaurant',
    @housing_capacity = 3;

SELECT * FROM Reservations
SELECT * FROM ActionLog
DELETE FROM ActionLog
DELETE Reservations
DELETE Housings

EXEC dbo.InsertReservationWithRecovery
    @skier_fname = 'Alex',
    @skier_lname = 'Miller',
    @skier_skill = 'advanced',
    @housing_name = 'Peak Stay',
    @housing_location = 'West Ridge',
    @housing_type = 'Hostel',	-- Invalid value
    @housing_capacity = 0;

SELECT * FROM Reservations
SELECT * FROM ActionLog
DELETE FROM ActionLog
DELETE Reservations
DELETE Housings

EXEC dbo.InsertReservationWithRecovery
    @skier_fname = 'Lorem',
    @skier_lname = 'Ipsum',
    @skier_skill = 'Beginner',
    @housing_name = 'Hill Zero',
    @housing_location = 'West Ridge',
    @housing_type = 'Restaurant',
    @housing_capacity = 0;	-- Invalid value

SELECT * FROM Reservations
SELECT * FROM ActionLog
DELETE FROM ActionLog
DELETE Reservations
DELETE Housings