<?php
error_reporting(E_ALL);
require_once("db_connect.php");
require_once("functions.php");
$html = file_get_contents("html/landing.html");

session_start();
echo $html;