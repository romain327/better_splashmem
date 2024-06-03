<?php
error_reporting(E_ALL);
require_once("functions.php");

session_start();
if(filesize("database/libs.csv") == 0) {
    $html_libs = "<p>Aucune librairie disponible.</p>";
}
else {
    $file = file_get_contents("database/libs.csv");
    $libs = array();
    $html_libs = "";
    $lines = explode("\n", $file);
    foreach ($lines as $line) {
        if($line != "") {
            $data = explode(";", $line);
            $libs[$data[1]] = $data[0];
        }
    }
    $lib_count = 1;
    foreach ($libs as $lib => $name) {
        $html_libs .= "<div class='check_lib'><input type='checkbox' name='lib" . $lib_count ."' value='" . $lib. "'><label>" . $lib . "</label></div>";
        $lib_count++;
    }
}
echo $html_libs;