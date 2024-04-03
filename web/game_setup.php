<?php
error_reporting(E_ALL);
require_once("functions.php");

session_start();
if(file_exists("game.zip")) {
    $zip = new ZipArchive();
    $zip->deleteName("game.zip");
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
$file = fopen("database/libs.csv", "r");
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
fwrite($file2, "cp libs/*.so /opt/splashmem/libs\n");
$file2_content = "/opt/splashmem/splash ";
foreach($libs as $key => $value) {
    $fill_name = str_pad($value, 30, "\0");
    $fill_lib = str_pad($key, 30, "\0");
    $file2_content .= "libs/".$key." ";
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
    echo "./" . $dir . "/" . $key;
    $zip->addFile("./" . $dir . "/" . $key, "libs/".$key);
}
$zip->addFile("start.sh");
$zip->addFile("game_config.bin");
$zip->close();

header("Content-type: application/zip");
header("Content-Disposition: attachment; filename=$archive_file_name");
header("Content-length: " . filesize("$archive_file_name"));
header("Pragma: no-cache");
header("Expires: 0");
readfile("$archive_file_name");