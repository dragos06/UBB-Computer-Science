<?php

header("Content-Type: application/json");
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

session_start();
require_once '../db/connection.php';

$method = $_SERVER['REQUEST_METHOD'];

switch ($method) {
    case "OPTIONS":
        http_response_code(200);
        exit;
    case "GET":
        try {
            $query = "SELECT * FROM tasks";
            $stmt = $pdo->prepare($query);
            $stmt->execute();
            echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
            break;
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching projects']);
        }
    case "PUT":
        $data = json_decode(file_get_contents("php://input"), true);

        if (!isset($data["id"], $data["status"])) {
            http_response_code(400);
            echo json_encode(['error' => 'Missing required fields']);
            exit;
        }

        try {
            $id = $data["id"];
            $status = $data["status"];
            $userId = $_SESSION['userid'];

            $stmt = $pdo->prepare("SELECT status FROM tasks WHERE id = ?");
            $stmt->execute([$id]);
            $oldStatus = $stmt->fetchColumn();


            $stmt = $pdo->prepare("UPDATE tasks SET status=?, lastUpdated = ? WHERE id=?");
            $stmt->execute([$status, date("Y-m-d h:i:s a", time()), $id]);

            $stmt = $pdo->prepare("INSERT INTO tasklog(taskId, userId, oldStatus, newStatus) VALUES (?, ?, ?, ?)");
            $stmt->execute([$id, $userId, $oldStatus, $status]);

            http_response_code(200);
            echo json_encode(['success' => true]);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while updating projects']);
        }
}

?>