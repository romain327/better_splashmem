<?php
error_reporting(E_ALL);
$html = file_get_contents("html/ranking.html");

session_start();
if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] ."</p>", $html);
    $html = str_replace("<!--[logout]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
}
echo $html;