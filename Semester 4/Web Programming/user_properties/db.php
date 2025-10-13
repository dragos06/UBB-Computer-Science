<?php

try {
    $pdo = new PDO("mysql:host=localhost;dbname=user_properties", "root", "");
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Database connection failes: " . $e->getMessage());
}

?>