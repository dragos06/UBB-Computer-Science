USE SkiResort

--======================================
--Dirty reads - CONNECTION 2
--======================================

-- Issue
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
PRINT 'Result without preventing the dirty reads'
SELECT lesson_price FROM Lessons WHERE lesson_duration=5;
GO

-- Solution
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
PRINT 'Result preventing the dirty reads'
SELECT lesson_price FROM Lessons WHERE lesson_duration=5;
GO

--======================================
-- Non-Repeatable Reads - CONNECTION 2
--======================================
BEGIN TRANSACTION
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;
	COMMIT;


--======================================
-- Phantom reads - CONNECTION 2
--======================================
BEGIN TRANSACTION;
	INSERT INTO Lessons (instructor_id, lesson_price, lesson_duration) VALUES (10, 200, 3);
	COMMIT;

DELETE FROM Lessons WHERE lesson_duration = 3;

--======================================
-- Deadlock - CONNECTION 1
--======================================
BEGIN TRANSACTION;
	UPDATE Lifts SET lift_capacity = lift_capacity + 20 WHERE lift_type='Gondola';

	WAITFOR DELAY '00:00:10';
	UPDATE Lessons SET lesson_price = lesson_price + 50 WHERE lesson_duration=5;
	COMMIT;