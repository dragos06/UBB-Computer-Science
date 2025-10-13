USE CulturalEvents

-- Issue: DEADLOCK: Since we're running by default on READ COMMITED, the X lock is released only at the end of the transaction.
--	So, T1 locks Categories until commit, T2 locks Buildings until commit,
-- T1 tries to read from Building but the X lock hasn't been yet released,
-- T2 tries to read from Categories but the X lock hasn't been yet released,
-- They enter a deadlock state, in which one transaction will be chosen as the victim, and the other transaction will commit
BEGIN TRANSACTION
	UPDATE Categories SET c_description = 'new description1' WHERE c_name = 'cat1';
	WAITFOR DELAY '00:00:10'
	UPDATE Buildings SET b_name = 'new name1' WHERE b_spaces=1;
	COMMIT;

SELECT * FROM Buildings
SELECT * FROM Categories

-- Solution: Update resources in the same order
BEGIN TRANSACTION
	UPDATE Buildings SET b_name = 'new name1' WHERE b_spaces=1;
	WAITFOR DELAY '00:00:10'
	UPDATE Categories SET c_description = 'new description1' WHERE c_name = 'cat1';
	COMMIT;

-- Another Solution: SET DEADLOCK_PRIORITY LOW; in order to target which transaction will be stopped