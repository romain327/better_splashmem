<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");

session_start();
$_SESSION["user"] = 0;
logout();
echo $html;