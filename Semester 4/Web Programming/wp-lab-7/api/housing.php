<?php

require_once '../db/connection.php';

header("Content-Type: application/json");

switch ($_SERVER['REQUEST_METHOD']) {
    case "GET":
        $stmt = $pdo->query("SELECT * FROM Housings");
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        break;
    case "POST":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("INSERT INTO Housings (name, location, capacity) VALUES (?, ?, ?)");
        $stmt->execute([$data["name"], $data["location"], $data["capacity"]]);
        break;
    case "DELETE":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("DELETE FROM Housings WHERE id = ?");
        $stmt->execute([$data["id"]]);
        echo json_encode(["success" => true]);
        break;
    case "PUT":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("UPDATE Housings SET name=?, location=?, capacity=? WHERE id = ?");
        $stmt->execute([$data["name"], $data["location"], $data["capacity"], $data["id"]]);
        echo json_encode(["success" => true]);
        break;
}

?>