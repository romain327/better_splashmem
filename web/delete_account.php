<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");

session_start();
$html = change_mode($html, "[css]", $_SESSION["mode"], "[icon]", $_SESSION["icon"], "[background]", $_SESSION["background"]);
$_SESSION["user"] = 0;
logout();
echo $html;