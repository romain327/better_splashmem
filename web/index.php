<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");
$light = file_get_contents("css/light.css");
$dark = file_get_contents("css/dark.css");

session_start();

if(isset($_SESSION["user"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] . "</p>", $html);
        $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon compte</a>', $html);
}

if (!isset($_SESSION["change_mode"])) {
    $_SESSION["change_mode"] = 0;
}

if(!isset($_SESSION["mode"])) {
    $_SESSION["mode"] = "dark.css";
}

if(!isset($_SESSION["icon"])) {
    $_SESSION["icon"] = "sun.svg";
}

if(!isset($_SESSION["background"])) {
    $_SESSION["background"] = "background1.mp4";
}

if($_SESSION["change_mode"] == 1) {
    if ($_SESSION["mode"] == "dark.css") {
        $html = change_mode($html, "[css]", "light.css", "[icon]", "moon.svg", "[background]", "background2.mp4");
        $_SESSION["mode"] = "light.css";
        $_SESSION["icon"] = "moon.svg";
        $_SESSION["background"] = "background2.mp4";
    } else {
        $html = change_mode($html, "[css]", "dark.css", "[icon]", "sun.svg", "[background]", "background1.mp4");
        $_SESSION["mode"] = "dark.css";
        $_SESSION["icon"] = "sun.svg";
        $_SESSION["background"] = "background1.mp4";
    }
    $_SESSION["change_mode"] = 0;
}
else {
    $html = change_mode($html, "[css]", $_SESSION["mode"], "[icon]", $_SESSION["icon"], "[background]", $_SESSION["background"]);
}

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color($_SESSION["mode"]);
$light = str_replace($color, $new_color, $light);
$dark = str_replace($color, $new_color, $dark);
file_put_contents("css/light.css", $light);
file_put_contents("css/dark.css", $dark);
file_put_contents("database/color.csv", $new_color);

if(isset($_FILES["file"])) {
    if(!isset($_SESSION["name"])) {
        $html = str_replace("<!--[upload_msg]-->", "<p>Vous devez d'abord choisir un pseudo.</p>", $html);
    }
    else {
        if($_SESSION["libs"] == 99) {
            $html = str_replace("<!--[upload_msg]-->", "<p>Vous avez atteint le nombre maximum de librairies. Vous pouvez en supprimer en allant sans <a class='menu_link' href='account.php'>Mon compte</a>.</p>", $html);
        }
        else {
            $target_dir = "player_libs/";
            $target_file = $target_dir . basename($_FILES["file"]["name"]);
            $filetype = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
            if($filetype != "so") {
                $html = str_replace("<!--[upload_msg]-->", "<p>Seul les fichiers .so sont acceptés.</p>", $html);
            }
            else {
                if(move_uploaded_file($_FILES["file"]["tmp_name"], $target_file)) {
                    $file = file_get_contents("database/user.csv");
                    $lines = explode("\n", $file);
                    foreach($lines as $line) {
                        $data = explode(";", $line);
                        $file_data = $data[0] . ";" . $data[1] . ";" . $data[2] . "\n";
                        while(check_lib_exists($_SESSION["name"], $_SESSION["libs"])) {
                            $_SESSION["libs"]++;
                        }
                        $new_file_data = $data[0] . ";" . $data[1] . ";" . $_SESSION["libs"] . "\n";
                        $file = str_replace($file_data, $new_file_data, $file);
                    }
                    file_put_contents("database/user.csv", $file);
                    $lib_name = rename_lib_as_player_name(basename($_FILES["file"]["name"], ".so"), $_SESSION["name"], $_SESSION["libs"]);
                    file_put_contents("database/libs.csv", $_SESSION["name"] . ";" . $lib_name . ";" . get_date() ."\n", FILE_APPEND);
                    $html = str_replace("<!--[upload_msg]-->", "<p>Fichier chargé avec succès.</p>", $html);
                }
                else {
                    $html = str_replace("<!--[upload_msg]-->", "<p>Erreur lors du chargement du fichier.</p>", $html);
                }
            }
        }
    }
}
echo $html;