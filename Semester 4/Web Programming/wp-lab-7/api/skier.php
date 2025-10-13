<?php

require_once '../db/connection.php';

header("Content-Type: application/json");

switch ($_SERVER['REQUEST_METHOD']) {
    case "GET":
        $stmt = $pdo->query("SELECT * FROM Skiers");
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        break;
    case "POST":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("INSERT INTO Skiers (name, email) VALUES (?, ?)");
        $stmt->execute([$data["name"], $data["email"]]);
        break;
    case "DELETE":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("DELETE FROM Skiers WHERE id = ?");
        $stmt->execute([$data["id"]]);
        echo json_encode(["success" => true]);
        break;
    case "PUT":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("UPDATE Skiers SET name=?, email=? WHERE id = ?");
        $stmt->execute([$data["name"], $data["email"], $data["id"]]);
        echo json_encode(["success" => true]);
        break;
}

?>