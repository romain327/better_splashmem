<?php
error_reporting(E_ALL);
require_once("db_connect.php");
$html = file_get_contents("html/landing.html");

session_start();
$view = "CREATE VIEW wiew1 AS SELECT user_name, MAX(score) AS best_score FROM sp_score GROUP BY user_name;";
mysqli_query($conn, $view);
$ranking = "<table><tr><th colspan='2'>Classement</th></tr>";
$sql_ranking = "SELECT user_name, best_score FROM sp_user INNER JOIN wiew1 USING(user_name) ORDER BY best_score DESC LIMIT 10;";
try {
    $stmt = mysqli_stmt_init($conn);
    mysqli_stmt_prepare($stmt, $sql_ranking);
    mysqli_stmt_bind_param($stmt, "s", $name);
    if (mysqli_stmt_execute($stmt)) {
        $result_ranking = mysqli_stmt_get_result($stmt);
        $i = 1;
        while ($row = mysqli_fetch_row($result_ranking)) {
            $ranking .= "<tr><td>" . $i . "</td><td>" . $row["user_name"] . "</td></tr>";
            $i++;
        }
    } else {
        echo "Erreur lors de la requête : " . mysqli_error($conn);
    }
}
catch (Exception $e) {
    echo "Erreur lors de la requête : " . $e->getMessage();
}
$drop_view = "DROP VIEW wiew1;";
mysqli_query($conn, $drop_view);

$html = str_replace("[ranking]", $ranking . "</table>", $html);
echo $html;