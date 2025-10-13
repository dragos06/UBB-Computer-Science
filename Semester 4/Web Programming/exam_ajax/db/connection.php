<?php

try{
    $pdo = new PDO("mysql:host=localhost;dbname=exam_db", "root", "");
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch(PDOException $e){
    die("Database connection failes: " . $e->getMessage());
}

?>