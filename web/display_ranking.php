<?php
error_reporting(E_ALL);

session_start();
$html_ranking = "<table><th colspan='4'>Classement</th>
<tr><th>Place</th><th>Nom</th><th>Librairie</th><th>Score</th></tr>";
if(filesize("database/score.csv") != 0) {
    $file = fopen("database/score.csv", "r");
    $ranking = array();
    while (!feof($file)) {
        $line = fgets($file);
        $line = explode(";", $line);
        $ranking[$line[1]] = array($line[0], $line[2], $line[3]);
    }
    fclose($file);
    krsort($ranking, SORT_NUMERIC);
    $rank = 1;
    foreach ($ranking as $lib => $data) {
        $html_ranking .= "<tr><td>" . $rank . "</td><td>" . $data[0] . "</td><td>" . $lib . "</td><td>" . $data[1] . "</td><td>" . $data[2] . "</td></tr>";
        $rank++;
    }
}
$html_ranking .= "</table>";
echo $html_ranking;