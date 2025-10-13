USE SkiResort

GO
CREATE OR ALTER PROCEDURE dbo.InsertReservationWithRecovery
    @skier_fname VARCHAR(30),
    @skier_lname VARCHAR(30),
    @skier_skill VARCHAR(30),
    @housing_name VARCHAR(30),
    @housing_location VARCHAR(30),
    @housing_type VARCHAR(30),
    @housing_capacity SMALLINT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @err_msg NVARCHAR(4000)

	BEGIN TRY
		BEGIN TRANSACTION;

			IF @skier_skill NOT IN ('Beginner', 'Intermediate', 'Advanced')
				THROW 51000, 'Invalid skier skill. Must be: Beginner, Intermediate, or Advanced.', 1;
			INSERT INTO dbo.Skiers (skier_fname, skier_lname, skier_skill)
			VALUES (@skier_fname, @skier_lname, @skier_skill);

			DECLARE @skier_id INT = SCOPE_IDENTITY();

			INSERT INTO dbo.ActionLog (action, status, message)
			VALUES (
				'InsertSkierWithValidation',
				'Success',
				CONCAT('Skier added: SkierID=', @skier_id)
			);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK;

		SET @err_msg = ERROR_MESSAGE();

        INSERT INTO dbo.ActionLog (action, status, message)
        VALUES (
            'InsertSkierWithValidation',
            'Failure',
            @err_msg
        );
	END CATCH

	BEGIN TRY
		BEGIN TRANSACTION;

			IF @housing_type NOT IN ('Restaurant', 'Cabin', 'Hotel')
				THROW 51001, 'Invalid housing type. Must be: Restaurant, Cabin, or Hotel.', 1;
			IF @housing_capacity <= 0
				THROW 51002, 'Housing capacity must be greater than zero.', 1;
			INSERT INTO dbo.Housings (housing_name, housing_location, housing_type, housing_capacity)
			VALUES (@housing_name, @housing_location, @housing_type, @housing_capacity);
		
			DECLARE @housing_id INT = SCOPE_IDENTITY();

			INSERT INTO dbo.ActionLog (action, status, message)
			VALUES (
				'InsertHousingWithValidation',
				'Success',
				CONCAT('Housing added: HousingID=', @housing_id)
			);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK;

		SET @err_msg = ERROR_MESSAGE();

        INSERT INTO dbo.ActionLog (action, status, message)
        VALUES (
            'InsertHousingWithValidation',
            'Failure',
            @err_msg
        );
	END CATCH

	BEGIN TRY
		BEGIN TRANSACTION;

			IF @skier_id IS NULL
				THROW 51003, 'SkierID not found.', 1;
			
			IF @housing_id IS NULL
				THROW 51004, 'HousingID not found.', 1;

			INSERT INTO dbo.Reservations (skier_id, housing_id)
			VALUES (@skier_id, @housing_id);

			INSERT INTO dbo.ActionLog (action, status, message)
			VALUES (
				'InsertReservationWithValidation',
				'Success',
				CONCAT('Reservation added: SkierID=', @skier_id, ', HousingID=', @housing_id)
			);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK;

		SET @err_msg = ERROR_MESSAGE();

        INSERT INTO dbo.ActionLog (action, status, message)
        VALUES (
            'InsertReservationWithValidation',
            'Failure',
            @err_msg
        );
	END CATCH
END