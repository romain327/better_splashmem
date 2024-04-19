<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/rules.html");
$css = file_get_contents("css/colors.css");

session_start();

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color();
$css = str_replace($color, $new_color, $css);
file_put_contents("css/colors.css", $css);
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