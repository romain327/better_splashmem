<?php
error_reporting(E_ALL);
require_once("functions.php");
$css = file_get_contents("css/light.css");

session_start();

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color($_SESSION["mode"]);
$css = str_replace($color, $new_color, $css);
file_put_contents("css/light.css", $css);
file_put_contents("database/color.csv", $new_color);

logout();
header("Location: index.php");