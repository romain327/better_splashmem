<?php
error_reporting(E_ALL);
require_once("db_connect.php");
$html = file_get_contents("html/landing.html");

session_start();
if(isset($_POST["name_nac"])) {
    $name = $_POST["name_nac"];
    $sql = "INSERT INTO sp_user(name, ranking) VALUES(?, 0)";
    $stmt = mysqli_stmt_init($conn);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "s", $name);
    mysqli_stmt_execute($stmt);
    $_SESSION["name"] = $name;
    $html = str_replace("<!--[name]-->", "<p>" . $name ."</p>", $html);
}
elseif(isset($_POST["name"]) && isset($_POST["password"])) {
    $name = $_POST["name"];
    $password = sha1($_POST["password"]);
    $sql = "SELECT * FROM sp_user WHERE name = ? AND password = ?";
    $stmt = mysqli_stmt_init($conn);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ss", $name, $password);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
    if($result->num_rows == 1) {
        $_SESSION["name"] = $name;
        $html = str_replace("<!--[name]-->", "<p>" . $name ."</p>", $html);
    }
    else {
        $html = str_replace("<!--[name]-->", "<p>Identifiants incorrects.</p>", $html);
    }
}
elseif(isset($_POST["name2"]) && isset($_POST["password2"]) && isset($_POST["password3"])) {
    $name = $_POST["name2"];
    $password = sha1($_POST["password2"]);
    $password2 = sha1($_POST["password3"]);
    if($password != $password2) {
        $html = str_replace("<!--[name]-->", "<p>Les mots de passe ne correspondent pas.</p>", $html);
    }
    else {
        $sql = "SELECT * FROM sp_user WHERE name = ?";
        $stmt = mysqli_stmt_init($conn);
        mysqli_stmt_prepare($stmt, $sql);
        mysqli_stmt_bind_param($stmt, "s", $name);
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        if($result->num_rows == 1) {
            $html = str_replace("<!--[name]-->", "<p>Ce nom est déjà pris.</p>", $html);
        }
        else {
            $sql = "INSERT INTO sp_user(name, password, ranking) VALUES(?, ?, 0)";
            $stmt = mysqli_stmt_init($conn);
            mysqli_stmt_prepare($stmt, $sql);
            mysqli_stmt_bind_param($stmt, "ss", $name, $password);
            mysqli_stmt_execute($stmt);
            $_SESSION["name"] = $name;
            $html = str_replace("<!--[name]-->", "<p>" . $name ."</p>", $html);
        }
    }
}
echo $html;