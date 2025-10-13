<!DOCTYPE html>
<html>

<head>
    <title>Create Reservation</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <button id="backButton" type="button" style="width: 10%">Back</button>
    <h2>New Reservation</h2>
    <form id="reservationForm">
        <select name="skier_id" required></select>
        <select name="housing_id" required></select>
        <input type="date" name="start_date" required>
        <input type="date" name="end_date" required>
        <button type="submit">Reserve</button>
    </form>

    <script src="../js/reservation.js"></script>
</body>

</html>