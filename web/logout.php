<?php
error_reporting(E_ALL);

session_start();
if($_SESSION["user"] == 0) {
    $file = file_get_contents("database/user.csv");
    $lines = explode("\n", $file);
    foreach ($lines as $key => $line) {
        $data = explode(";", $line);
        if($data[0] == $_SESSION["name"]) {
            unset($lines[$key]);
        }
    }
    $file = implode("\n", $lines);
    file_put_contents("database/user.csv", $file);

    $file = file_get_contents("database/score.csv");
    $lines = explode("\n", $file);
    foreach ($lines as $key => $line) {
        $data = explode(";", $line);
        if($data[0] == $_SESSION["name"]) {
            unset($lines[$key]);
        }
    }
    $file = implode("\n", $lines);
    file_put_contents("database/score.csv", $file);
}
session_destroy();
header("Location: index.php");