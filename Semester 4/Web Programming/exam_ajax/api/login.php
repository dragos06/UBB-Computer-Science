<?php

session_start();
require '../db/connection.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = json_decode(file_get_contents("php://input"), true);
    $name = $data["name"];
    $stmt = $pdo->prepare("SELECT id, username FROM users WHERE username = :name");
    $stmt->bindValue(':name', $name, PDO::PARAM_STR);
    $stmt->execute();

    $user = $stmt->fetch(PDO::FETCH_ASSOC);
    if ($user) {
        $_SESSION['userid'] = $user['id'];
        $_SESSION['username'] = $name;
        http_response_code(200);
        echo json_encode(['success' => true]);
        exit();
    } else {
        http_response_code(500);
        echo json_encode(['error' => 'Database error while fetching developers']);
    }
}
?>