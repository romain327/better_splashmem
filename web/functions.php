<?php
function rename_lib_as_player_name($curr_name, $player_name, $nb_libs) {
    $target_dir = "player_libs/";
    $old = $target_dir . $curr_name . ".c";
    $new = $target_dir . $player_name . "v". $nb_libs . ".c";
    rename($old, $new);
    $data = explode("/", $new);
    $new = $data[1];
    return $new;
}