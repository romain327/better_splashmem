<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");
$css = file_get_contents("css/light.css");

session_start();

$html = change_mode($html, "[css]", $_SESSION["mode"], "[icon]", $_SESSION["icon"], "[background]", $_SESSION["background"]);

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color($_SESSION["mode"]);
$css = str_replace($color, $new_color, $css);
file_put_contents("css/light.css", $css);
file_put_contents("database/color.csv", $new_color);

if(isset($_SESSION["user"])) {
    logout();
}
@session_start();
if (isset($_POST["name_nac"])) {
    $name = $_POST["name_nac"];
    $file = file_get_contents("database/user.csv");
    $lines = explode("\n", $file);
    $used = false;
    foreach ($lines as $line) {
        $data = explode(";", $line);
        if ($data[0] == $name) {
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
} elseif (isset($_POST["name"]) && isset($_POST["password"])) {
    $name = $_POST["name"];
    $password = sha1($_POST["password"]);
    $lines = file("database/user.csv");
    $size = count($lines);
    $found = false;
    while (!$found && $size > 0) {
        $size--;
        $line = $lines[$size];
        $data = explode(";", $line);
        if ($data[0] == $name && $data[1] == $password) {
            $found = true;
            $_SESSION["name"] = $name;
            $_SESSION["password"] = $password;
            $_SESSION["libs"] = $data[2];
            $_SESSION["user"] = 1;
            $html = str_replace("<!--[name]-->", "<p>" . $name . "</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
        }
    }
    if (!$found) {
        $html = str_replace("<!--[login_error_connect]-->", "<p>Identifiants incorrects.</p>", $html);
    }
} elseif (isset($_POST["name2"]) && isset($_POST["password2"]) && isset($_POST["password3"])) {
    echo "test";
    $name = $_POST["name2"];
    $password = sha1($_POST["password2"]);
    $password2 = sha1($_POST["password3"]);
    if ($password != $password2) {
        $html = str_replace("<!--[login_error_create]-->", "<p>Les mots de passe ne correspondent pas.</p>", $html);
    } else {
        $lines = file("database/user.csv");
        $size = count($lines);
        $found = false;
        while (!$found && $size > 0) {
            $size--;
            $line = $lines[$size];
            $data = explode(";", $line);
            if ($data[0] == $name) {
                $found = true;
                $html = str_replace("<!--[login_error_create]-->", "<p>Ce nom est déjà pris.</p>", $html);
            }
        }
        if (!$found) {
            logout();
            session_start();
            $line = $name . ";" . $password . ";0\n";
            file_put_contents("database/user.csv", $line, FILE_APPEND);
            $_SESSION["name"] = $name;
            $_SESSION["password"] = $password;
            $_SESSION["libs"] = 0;
            $_SESSION["user"] = 1;
            $html = str_replace("<!--[name]-->", "<p>" . $name . "</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
        }
    }
} else {
    if (isset($_SESSION["name"])) {
        if ($_SESSION["user"] == 0) {
            $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] . "</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
        } else {
            $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] . "</p>", $html);
            $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
        }
    }
}
echo $html;