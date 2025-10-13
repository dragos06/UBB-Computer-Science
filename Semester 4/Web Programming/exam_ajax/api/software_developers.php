<?php

header("Content-Type: application/json");
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

require_once '../db/connection.php';

$method = $_SERVER['REQUEST_METHOD'];

switch ($method){
    case "OPTIONS":
        http_response_code(200);
        exit;
    case "GET":
        try{
            $query = "SELECT * FROM software_developers";
            $stmt = $pdo->prepare($query);
            $stmt->execute();
            echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
            break;
        }
        catch(PDOException $e){
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching developers']);
        }
}

?>