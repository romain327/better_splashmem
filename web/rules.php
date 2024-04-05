<?php
error_reporting(E_ALL);
$html = file_get_contents("html/rules.html");

session_start();
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