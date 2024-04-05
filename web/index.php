<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");

session_start();
if(isset($_POST["name_nac"])) {
    $name = $_POST["name_nac"];
    $file = file_get_contents("database/user.csv");
    $lines = explode("\n", $file);
    $used = false;
    foreach ($lines as $line) {
        $data = explode(";", $line);
        if($data[0] == $name) {
            $html = str_replace("<!--[name_error]-->", "<p>Ce nom est déjà pris.</p>", $html);
            $used = true;
        }
    }
    if (!$used) {
        $line = $name . ";;0\n";
        file_put_contents("database/user.csv", $line, FILE_APPEND);
        $_SESSION["name"] = $name;
        $_SESSION["libs"] = 0;
        $_SESSION["user"] = 0;
        $html = str_replace("<!--[name]-->", "<p>" . $name . "</p>", $html);
        $html = str_replace("<!--[account]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
    }
}
elseif(isset($_POST["name"]) && isset($_POST["password"])) {
    $name = $_POST["name"];
    $password = sha1($_POST["password"]);
    $lines = file("database/user.csv");
    $size = count($lines);
    $found = false;
    while (!$found && $size > 0) {
        $size--;
        $line = $lines[$size];
        $data = explode(";", $line);
        if($data[0] == $name && $data[1] == $password) {
            $found = true;
            $_SESSION["name"] = $name;
            $_SESSION["password"] = $password;
            $_SESSION["libs"] = $data[2];
            $_SESSION["user"] = 1;
            $html = str_replace("<!--[name]-->", "<p>" . $name ."</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
        }
    }
    if(!$found) {
        $html = str_replace("<!--[login_error_connect]-->", "<p>Identifiants incorrects.</p>", $html);
    }
}
elseif(isset($_POST["name2"]) && isset($_POST["password2"]) && isset($_POST["password3"])) {
    $name = $_POST["name2"];
    $password = sha1($_POST["password2"]);
    $password2 = sha1($_POST["password3"]);
    if($password != $password2) {
        $html = str_replace("<!--[login_error_create]-->", "<p>Les mots de passe ne correspondent pas.</p>", $html);
    }
    else {
        $lines = file("database/user.csv");
        $size = count($lines);
        $found = false;
        while (!$found && $size > 0) {
            $size--;
            $line = $lines[$size];
            $data = explode(";", $line);
            if($data[0] == $name) {
                $found = true;
                $html = str_replace("<!--[login_error_create]-->", "<p>Ce nom est déjà pris.</p>", $html);
            }
        }
        if(!$found) {
            $line = $name . ";" . $password . ";0\n";
            file_put_contents("database/user.csv", $line, FILE_APPEND);
            $_SESSION["name"] = $name;
            $_SESSION["password"] = $password;
            $_SESSION["libs"] = 0;
            $_SESSION["user"] = 1;
            $html = str_replace("<!--[name]-->", "<p>" . $name ."</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
        }
    }
}
else {
    if(isset($_SESSION["name"])) {
        $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] ."</p>", $html);
        $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
    }
}

if(isset($_FILES["file"])) {
    if (!isset($_SESSION["name"])) {
        $html = str_replace("<!--[upload_msg]-->", "<p>Vous devez d'abord choisir un pseudo.</p>", $html);
    } else {
        $target_dir = "player_libs/";
        if (isset($_FILES["file"])) {
            $target_file = $target_dir . basename($_FILES["file"]["name"]);
            $filetype = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
            if ($filetype != "so") {
                $html = str_replace("<!--[upload_msg]-->", "<p>Seul les fichiers .c sont acceptés.</p>", $html);
            } else {
                if (move_uploaded_file($_FILES["file"]["tmp_name"], $target_file)) {
                    $file = file_get_contents("database/user.csv");
                    $lines = explode("\n", $file);
                    foreach ($lines as $line) {
                        $data = explode(";", $line);
                        if ($data[0] == $_SESSION["name"]) {
                            $file_data = $data[0] . ";" . $data[1] . ";" . $data[2] . "\n";
                            $_SESSION["libs"]++;
                            $new_file_data = $data[0] . ";" . $data[1] . ";" . $data[2] . "\n";
                        }
                    }
                    $file = str_replace($file_data, $new_file_data, $file);
                    $nb_libs = $_SESSION["libs"];
                    file_put_contents("database/user.csv", $file);
                    $lib_name = rename_lib_as_player_name(basename($_FILES["file"]["name"], ".c"), $_SESSION["name"], $nb_libs);
                    file_put_contents("database/score.csv", $_SESSION["name"] . ";" . $lib_name.";" . "0\n", FILE_APPEND);
                    $html = str_replace("<!--[upload_msg]-->", "<p>Fichier chargé avec succès.</p>", $html);
                } else {
                    $html = str_replace("<!--[upload_msg]-->", "<p>Erreur lors du chargement du fichier.</p>", $html);
                }
            }
        }
    }
}

echo $html;