<?php
function rename_lib_as_player_name($curr_name, $player_name) {
    $target_dir = "player_libs/";
    $old = $target_dir . $curr_name . ".c";
    $new = $target_dir . $player_name . ".c";
    rename($old, $new);
}

function retrieve_ranking($conn, $html) {
    $view = "CREATE VIEW wiew1 AS SELECT user_name, MAX(score) AS best_score FROM sp_score GROUP BY user_name;";
    mysqli_query($conn, $view);
    $ranking = "<table><tr><th colspan='2'>Classement</th></tr>";
    $sql_ranking = "SELECT user_name, best_score FROM sp_user INNER JOIN wiew1 USING(user_name) ORDER BY best_score DESC LIMIT 10;";
    $result_ranking = mysqli_query($conn, $sql_ranking);
    $i = 1;
    while ($row = mysqli_fetch_row($result_ranking)) {
        $ranking .= "<tr><td>" . $i . "</td><td>" . $row["user_name"] . "</td></tr>";
        $i++;
    }

    $drop_view = "DROP VIEW wiew1;";
    mysqli_query($conn, $drop_view);

    $html = str_replace("[ranking]", $ranking . "</table>", $html);
    return $html;
}