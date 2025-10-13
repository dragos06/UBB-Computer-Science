<?php

$pdo = new PDO("mysql:host=localhost;dbname=document_manager", "root", "");
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

?>