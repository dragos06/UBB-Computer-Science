USE SkiResort

--======================================
-- Dirty reads - CONNECTION 1
--======================================
BEGIN TRANSACTION
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10';
	ROLLBACK;

--======================================
-- Non-Repeatable Read - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	SELECT lesson_price FROM Lessons WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10'
	SELECT lesson_price FROM Lessons WHERE lesson_duration=5;
	COMMIT;

-- Solution
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
BEGIN TRANSACTION
	SELECT lesson_price FROM Lessons WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10'
	SELECT lesson_price FROM Lessons WHERE lesson_duration=5;
	COMMIT;

SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

--======================================
-- Phantom Read - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	SELECT * FROM Lessons WHERE lesson_duration=3;

	WAITFOR DELAY '00:00:10';
	SELECT * FROM Lessons WHERE lesson_duration=3;
	COMMIT;

-- Solution
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRANSACTION
	SELECT * FROM Lessons WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10';
	SELECT * FROM Lessons WHERE lesson_duration=5;
	COMMIT;

SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

--======================================
-- Deadlock - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10'
	UPDATE Lifts SET lift_capacity = lift_capacity + 20 WHERE lift_type='Gondola';
	COMMIT;

-- Solution priority low - this will be the deadlock victim
SET DEADLOCK_PRIORITY LOW;
BEGIN TRANSACTION
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10'
	UPDATE Lifts SET lift_capacity = lift_capacity + 20 WHERE lift_type='Gondola';
	COMMIT;

-- Solution locking in the same order
BEGIN TRANSACTION
	UPDATE Lifts SET lift_capacity = lift_capacity + 20 WHERE lift_type='Gondola';

	WAITFOR DELAY '00:00:10'
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;
	COMMIT;

SELECT * FROM Lessons
SELECT * FROM Lifts