<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");
session_start();

if(!isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>Vous devez d'abord choisir un nom.</p>", $html);
}
else {
    $target_dir = "player_libs/";
    if(isset($_FILES["file"])) {
        $target_file = $target_dir . basename($_FILES["file"]["name"]);
        $filetype = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
        if($filetype != "c") {
            $html = str_replace("<!--[upload_msg]-->", "<p>Seul les fichiers .c sont acceptés.</p>", $html);
        }
        else {
            if (move_uploaded_file($_FILES["file"]["tmp_name"], $target_file)) {
                rename_lib_as_player_name(basename($_FILES["file"]["name"], ".c"), $_SESSION["name"]);
                $html = str_replace("<!--[upload_msg]-->", "<p>Fichier chargé avec succès.</p>", $html);
            } else {
                $html = str_replace("<!--[upload_msg]-->", "<p>Erreur lors du chargement du fichier.</p>", $html);
            }
        }
    }
}

echo $html;
