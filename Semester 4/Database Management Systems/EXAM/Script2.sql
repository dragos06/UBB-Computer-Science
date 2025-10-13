USE CulturalEvents

BEGIN TRANSACTION
	UPDATE Buildings SET b_name = 'new name2' WHERE b_spaces=1;
	WAITFOR DELAY '00:00:10'
	UPDATE Categories SET c_description = 'new description2' WHERE c_name = 'cat1';
	COMMIT;