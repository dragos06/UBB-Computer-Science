<!DOCTYPE html>
<html>

<head>
    <title>Housings</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <button id="backButton" type="button" style="width: 10%">Back</button>
    <h2>Housings</h2>
    <form id="addHousingForm">
        <input type="text" name="name" placeholder="Name" required>
        <input type="text" name="location" placeholder="Location" required>
        <input type="number" name="capacity" placeholder="Capacity" required>
        <button type="submit">Add Housing</button>
    </form>
    <ul id="housingList"></ul>

    <div id="editModal" class="modal">
        <div class="modal-content">
            <span id="closeModal" class="close">&times;</span>
            <h3>Edit Skier</h3>
            <form id="editHousingForm">
                <input type="hidden" name="id" />
                <input type="text" name="name" placeholder="Name" required />
                <input type="text" name="location" placeholder="Location" required />
                <input type="number" name="capacity" placeholder="Capacity" required />
                <button type="submit">Save</button>
            </form>
        </div>
    </div>

    <script src="../js/housing.js"></script>
</body>

</html>