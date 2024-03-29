<?php
error_reporting(E_ALL);
$html = file_get_contents("html/install.html");

session_start();
if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] ."</p>", $html);
}
echo $html;