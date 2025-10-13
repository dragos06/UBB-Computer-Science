USE ParkingLots

BEGIN TRANSACTION
	INSERT INTO Categories(c_name) VALUES ('cat1');
	COMMIT;