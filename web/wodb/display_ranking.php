<?php
error_reporting(E_ALL);

session_start();
$file = fopen("database/score.csv", "r");
$ranking = array();
while (!feof($file)) {
    $line = fgets($file);
    $line = explode(";", $line);
    $ranking[$line[1]] = $line[0];
}
fclose($file);
krsort($ranking, SORT_NUMERIC);
$rank = 1;
$html_ranking = "<table><th colspan='3'>Classement</th>
<tr><th>Place</th><th>Nom</th><th>Score</th></tr>";
while ($rank <= count($ranking)) {
    $html_ranking .= "<tr><td>" . $rank . "</td><td>" . current($ranking) . "</td><td>" . key($ranking) . "</td></tr>";
    next($ranking);
    $rank++;
}
$html_ranking .= "</table>";
echo $html_ranking;