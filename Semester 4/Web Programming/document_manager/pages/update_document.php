<!DOCTYPE html>
<html>

<head>
    <title>Update Document</title>
    <script src="../js/update_document.js" defer></script>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <h1>Update Document</h1>

    <ul id="docList"></ul>

    <div id="editModal" class="modal">
        <div class="modal-content">
            <span id="closeModal" class="close">&times;</span>
            <h3>Update Document</h3>
            <form id="editDocumentForm">
                <input type="hidden" name="id">
                <input type="text" name="author" placeholder="Author" required />
                <input type="text" name="title" placeholder="Title" required />
                <input type="number" name="pages" placeholder="Pages" required />
                <input type="text" name="type" placeholder="Type" required />
                <input type="text" name="format" placeholder="Format" required />
                <button type="submit">Save</button>
            </form>
        </div>
    </div>

    <a href="index.php">Back</a>
</body>

</html>