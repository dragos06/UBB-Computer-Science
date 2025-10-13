USE SmartHomes

BEGIN TRANSACTION
	UPDATE Homes SET h_name = 'new' WHERE r_id=1
	COMMIT;