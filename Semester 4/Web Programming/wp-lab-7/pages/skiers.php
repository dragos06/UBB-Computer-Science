<!DOCTYPE html>
<html>

<head>
    <title>Skiers</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <button id="backButton" type="button" style="width: 10%">Back</button>
    <h2>Skiers</h2>
    <form id="addSkierForm">
        <input type="text" name="name" placeholder="Name" required>
        <input type="email" name="email" placeholder="Email" required>
        <button type="submit">Add Skier</button>
    </form>
    <ul id="skierList"></ul>

    <div id="editModal" class="modal">
        <div class="modal-content">
            <span id="closeModal" class="close">&times;</span>
            <h3>Edit Skier</h3>
            <form id="editSkierForm">
                <input type="hidden" name="id"/>
                <input type="text" name="name" placeholder="Name" required />
                <input type="email" name="email" placeholder="Email" required />
                <button type="submit">Save</button>
            </form>
        </div>
    </div>

    <script src="../js/skier.js"></script>
</body>

</html>