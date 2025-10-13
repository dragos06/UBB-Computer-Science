ALTER DATABASE SkiResort SET ALLOW_SNAPSHOT_ISOLATION ON;

USE SkiResort

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRANSACTION

	DECLARE @lesson_price INT;
	SELECT @lesson_price = lesson_price FROM Lessons WHERE lesson_duration = 5;

	SELECT lesson_price FROM Lessons WHERE lesson_duration=5;

	WAITFOR DELAY '00:00:10'

	UPDATE Lessons
	SET lesson_price = @lesson_price + 50
	WHERE lesson_duration=5;

	COMMIT;

SELECT * FROM Lessons WHERE lesson_duration = 5;
