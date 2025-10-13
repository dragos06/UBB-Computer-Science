CREATE OR ALTER PROCEDURE dbo.InsertReservationWithValidation
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

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Validation
        IF @skier_skill NOT IN ('Beginner', 'Intermediate', 'Advanced')
            THROW 51000, 'Invalid skier skill. Must be: Beginner, Intermediate, or Advanced.', 1;
		IF @housing_type NOT IN ('Restaurant', 'Cabin', 'Hotel')
			THROW 51001, 'Invalid housing type. Must be: Restaurant, Cabin, or Hotel.', 1;
        IF @housing_capacity <= 0
            THROW 51002, 'Housing capacity must be greater than zero.', 1;

        -- Insert skier
        INSERT INTO dbo.Skiers (skier_fname, skier_lname, skier_skill)
        VALUES (@skier_fname, @skier_lname, @skier_skill);

        DECLARE @skier_id INT = SCOPE_IDENTITY();

        -- Insert housing
        INSERT INTO dbo.Housings (housing_name, housing_location, housing_type, housing_capacity)
        VALUES (@housing_name, @housing_location, @housing_type, @housing_capacity);

        DECLARE @housing_id INT = SCOPE_IDENTITY();

        -- Insert reservation
        INSERT INTO dbo.Reservations (skier_id, housing_id)
        VALUES (@skier_id, @housing_id);

        -- Log success
        INSERT INTO dbo.ActionLog (action, status, message)
        VALUES (
            'InsertReservationWithValidation',
            'Success',
            CONCAT('Reservation added: SkierID=', @skier_id, ', HousingID=', @housing_id)
        );

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @err_msg NVARCHAR(4000) = ERROR_MESSAGE();

        INSERT INTO dbo.ActionLog (action, status, message)
        VALUES (
            'InsertReservationWithValidation',
            'Failure',
            @err_msg
        );

        THROW;
    END CATCH
END
GO