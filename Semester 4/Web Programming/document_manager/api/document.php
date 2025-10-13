<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

require_once '../db/connection.php';

$method = $_SERVER['REQUEST_METHOD'];

switch ($method) {
    case "GET":
        $type = $_GET["type"] ?? null;
        $format = $_GET["format"] ?? null;

        $query = "SELECT * FROM Documents WHERE 1";
        $params = [];

        if ($type) {
            $query .= " AND type = ?";
            $params[] = $type;
        }
        if ($format) {
            $query .= " AND format = ?";
            $params[] = $format;
        }

        $stmt = $pdo->prepare($query);
        $stmt->execute($params);
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        break;

    case "POST":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("INSERT INTO Documents (author, title, pages, type, format) VALUES (?, ?, ?, ?, ?)");
        $stmt->execute([$data["author"], $data["title"], $data["pages"], $data["type"], $data["format"]]);
        echo json_encode(["success" => true]);
        break;

    case "PUT":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("UPDATE Documents SET author=?, title=?, pages=?, type=?, format=? WHERE id=?");
        $stmt->execute([$data["author"], $data["title"], $data["pages"], $data["type"], $data["format"], $data["id"]]);
        echo json_encode(["success" => true]);
        break;

    case "DELETE":
        $data = json_decode(file_get_contents("php://input"), true);
        $stmt = $pdo->prepare("DELETE FROM Documents WHERE id=?");
        $stmt->execute([$data["id"]]);
        echo json_encode(["success" => true]);
        break;
}


?>