<?php

header("Content-Type: application/json");
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

require_once '../db/connection.php';

$method = $_SERVER['REQUEST_METHOD'];

switch ($method) {
    case "OPTIONS":
        http_response_code(200);
        exit;
    case "GET":
        try {
            $query = "SELECT * FROM products";
            $stmt = $pdo->prepare($query);
            $stmt->execute();
            echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
            break;
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching products']);
        }
    case "POST":
        $data = json_decode(file_get_contents("php://input"), associative: true);

        if (!isset($data["username"], $data["products"])) {
            http_response_code(400);
            echo json_encode(['error' => 'Missing required fields']);
            exit;
        }

        try {
            $products = $data["products"];
            $username = $data["username"];
            $stmt = $pdo->prepare("SELECT id FROM users WHERE username = ?");
            $stmt->execute([$username]);
            $userId = $stmt->fetchColumn();

            $totalPrice = 0;
            $names = [];
            foreach ($products as $product) {
                $stmt = $pdo->prepare(query: "SELECT name, price FROM products WHERE id = ?");
                $stmt->execute([$product]);

                $row = $stmt->fetch(PDO::FETCH_ASSOC);
                if ($row) {
                    $exploded = explode("-", $row['name']);
                    $names[] = $exploded[0];
                    $totalPrice += $row['price'];
                }
            }

            $length = count($products);

            $discount = 0;

            if ($length >= 3) {
                $discount = 10;
            }

            $frequency = array_count_values($names);

            foreach ($frequency as $key => $value) {
                if ($value >= 2) {
                    $discount += 5;
                    break;
                }
            }


            
            $stmt = $pdo->prepare("SELECT oi.product_id 
                                        FROM (SELECT id FROM orders WHERE user_id = ? LIMIT 3) o INNER JOIN order_items oi ON o.id = oi.order_id"
            );
            $stmt->execute([$userId]);
            $products_ids = $stmt->fetchAll();
            $productNames = [];
            foreach ($products_ids as $product_id) {
                $stmt = $pdo->prepare(query: "SELECT name FROM products WHERE id = ?");
                $stmt->execute([$product_id]);

                $productNames[] = explode("-",$stmt->fetchColumn())[0];
            }





            $price = $totalPrice - $totalPrice * ($discount / 100);
            $stmt = $pdo->prepare("INSERT INTO orders(user_id, total_price) VALUES (?, ?)");
            $stmt->execute([$userId, $price]);

            $orderId = $pdo->lastInsertId();

            foreach ($products as $product) {
                $stmt = $pdo->prepare("INSERT INTO order_items(order_id, product_id) VALUES (?, ?)");
                $stmt->execute([$orderId, $product]);
            }

            http_response_code(200);
            echo json_encode(['success' => true, 'totalPrice' => $totalPrice]);

        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while updating projects']);
        }
}

?>