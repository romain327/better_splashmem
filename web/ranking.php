<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/ranking.html");
$light = file_get_contents("css/light.css");
$dark = file_get_contents("css/dark.css");

session_start();

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

if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] ."</p>", $html);
    if($_SESSION["user"] == 0) {
        $html = str_replace("<!--[account]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
    }
    else {
        $html = str_replace("<!--[account]-->", '<a class="menu_link" href="account.php">Mon Compte</a>', $html);
    }
}
echo $html;