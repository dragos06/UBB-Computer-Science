USE SkiResort

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRANSACTION

	DECLARE @lesson_price INT
	SELECT @lesson_price = lesson_price FROM Lessons WHERE lesson_duration=5;

	UPDATE Lessons
	SET lesson_price=@lesson_price + 50
	WHERE lesson_duration=5;

	COMMIT;