<?php
error_reporting(E_ALL);
require_once("db_connect.php");

session_start();
$ranking_content = "<table><tr><th colspan='3'>Classement</th></tr>
<tr><th>Position</th><th>Joueur</th><th>Score</th></tr>";
$sql_ranking = "SELECT user_name, MAX(score) AS best_score FROM sp_score GROUP BY user_name ORDER BY best_score DESC LIMIT 10";
$result_ranking = mysqli_query($conn, $sql_ranking);
$i = 1;
while ($row = mysqli_fetch_assoc($result_ranking)) {
    $ranking_content .= "<tr><td>" . $i . "</td><td>" . $row["user_name"] . "</td><td>". $row["best_score"] ."</td></tr>";
    $i++;
}
$ranking_content .= "</table>";

echo $ranking_content;