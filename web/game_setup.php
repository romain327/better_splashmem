<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/landing.html");

session_start();
if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] ."</p>", $html);
    $html = str_replace("<!--[logout]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
}

if(file_exists("game.zip")) {
    unlink("game.zip");
}

if(file_exists("start.sh")) {
    unlink("start.sh");
}

if(file_exists("game_config.bin")) {
    unlink("game_config.bin");
}

$libs = array();
foreach ($_POST as $key => $value) {
    $libs[$value] = null;
}
$keys = array_keys($libs);
$file = fopen("database/score.csv", "r");
foreach ($libs as $key => $value) {
    while(!feof($file)) {
        $line = fgets($file);
        $line = explode(";", $line);
        if (in_array($line[1], $keys)) {
            $libs[$line[1]] = $line[0];
        }
    }
}
fclose($file);

$file = fopen("game_config.bin", "w");
$file2 = fopen("start.sh", "w");
fwrite($file2, "#!/bin/bash\n");
fwrite($file2, "diretory=$(dirname -- $(readlink -fn -- \"$0\"))\n");
$file2_content = "./opt/splashmem/splash "."$"."directory/game_config.bin";
foreach($libs as $key => $value) {
    $fill_name = str_pad($value, 30, "\0");
    $fill_lib = str_pad($key, 30, "\0");
    $file2_content .= " $"."directory/libs/".$key;
    fwrite($file, $fill_name . $fill_lib);
}
$file2_content = str_replace("\n", "", $file2_content);
$file2_content = str_replace("\r", "", $file2_content);
fwrite($file2, $file2_content);
fclose($file);
fclose($file2);

$archive_file_name = "game.zip";
$dir = "player_libs";
$zip = new ZipArchive();
if ($zip->open($archive_file_name, ZIPARCHIVE::CREATE )!==TRUE) {
    exit("cannot open <$archive_file_name>\n");
}
$zip->addEmptyDir("libs");
foreach ($libs as $key => $value) {
    $key = str_replace("\r", "", $key);
    $key = str_replace("\n", "", $key);
    $key = str_replace(" ", "", $key);
    $zip->addFile("./" . $dir . "/" . $key, "libs/".$key);
}
$zip->addFile("start.sh");
$zip->addFile("game_config.bin");
$zip->close();
$html = str_replace("<!--[download]-->", '<a class="main_links" href="game.zip" download="game.zip">Télécharger</a>', $html);
echo $html;