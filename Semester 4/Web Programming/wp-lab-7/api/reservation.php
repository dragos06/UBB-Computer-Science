<?php

require_once("../db/connection.php");

header("Content-Type: application/json");

switch ($_SERVER['REQUEST_METHOD']) {
    case "GET":
        $stmt = $pdo->query("
            SELECT r.id, s.name AS skier_name, h.name AS housing_name, r.start_date, r.end_date
            FROM Skiers s 
            JOIN
            Reservations r ON s.id = r.skier_id
            JOIN Housings h ON r.housing_id = h.id 
        ");
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        break;
    case "POST":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("INSERT INTO Reservations (skier_id, housing_id, start_date, end_date) VALUES (?, ?, ?, ?)");
        $stmt->execute([$data["skier_id"], $data["housing_id"], $data["start_date"], $data["end_date"]]);
        break;
    case "DELETE":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("DELETE FROM Reservations WHERE id = ?");
        $stmt->execute([$data["id"]]);
        echo json_encode(["succes" => true]);
        break;
}

?>