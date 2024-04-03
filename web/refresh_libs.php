<?php
error_reporting(E_ALL);
require_once("functions.php");

session_start();
$file = fopen("database/libs.csv", "r");
$libs = array();
$html_libs = "";
if(filesize("database/libs.csv") == 0) {
    $html_libs = "<p>Aucune librairie disponible.</p>";
}
else {
    while(!feof($file)) {
        $line = fgets($file);
        $line = explode(";", $line);
        $libs[$line[1]] = $line[0];
    }
    fclose($file);
    $lib_count = 1;
    while($lib_count <= count($libs)) {
        $html_libs .= "<div class='check_lib'><input type='checkbox' name='lib" . $lib_count ."' value='" . key($libs) . "'><label>" . key($libs) . "</label></div>";
        next($libs);
        $lib_count++;
    }
}
echo $html_libs;