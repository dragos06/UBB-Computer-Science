CREATE TABLE ActionLog (
    log_id INT IDENTITY PRIMARY KEY,
    action NVARCHAR(100),
    status NVARCHAR(20),
    message NVARCHAR(MAX),
    log_time DATETIME DEFAULT GETDATE()
);

SELECT * FROM ActionLog