<?php
error_reporting(E_ALL);
require_once("functions.php");

session_start();
$html_ranking = "<table><th class='title' colspan='3'>Classement</th>
<tr><th>Place</th><th>Nom</th><th>Librairie</th><th>Score</th><th>Game master</th></tr>";
if(filesize("database/score.csv") != 0) {
    $file = file_get_contents("database/score.csv");
    $ranking = array();
    $lines = explode("\n", $file);
    foreach ($lines as $line) {
        $data = explode(";", $line);
        if($data[1] != "" && $data[0] != "" && $data[2] != "") {
            $ranking[$data[1]] = array($data[0], $data[2], $data[3]);
        }
    }
    krsort($ranking, SORT_NUMERIC);
    $rank = 1;
    foreach ($ranking as $lib => $data) {
        $html_ranking .= "<tr><td>" . $rank . "</td><td>" . $data[0] . "</td><td>" . $lib . "</td><td>" . $data[1] . "</td><td>" . $data[2] . "</td></tr>";
        $rank++;
    }
}
$html_ranking .= "</table>";
echo $html_ranking;