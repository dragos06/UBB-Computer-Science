<!DOCTYPE html>
<html>

<head>
    <title>Browse Documents</title>
    <script src="../js/browse_documents.js" defer></script>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <h1>Browse Documents</h1>

    <label>Type: <input type="text" id="typeFilter"></label>
    <label>Format: <input type="text" id="formatFilter"></label>
    <button onclick="loadDocuments()">Filter</button>

    <p id="lastFilter"></p>
    <ul id="docList"></ul>

    <a href="index.php">Back</a>
</body>

</html>