<!DOCTYPE html>
<html>

<head>
    <title>Add Document</title>
    <script src="../js/add_document.js" defer></script>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <h1>Add Document</h1>
    <form id="addForm">
        <input name="author" type="text" placeholder="Author" required>
        <input name="title" type="text" placeholder="Title" required>
        <input name="pages" type="number" placeholder="Pages" required>
        <input name="type" type="text" placeholder="Type" required>
        <input name="format" type="text" placeholder="Format" required>
        <button>Add Document</button>
    </form>

    <a href="index.php">Back</a>
</body>

</html>