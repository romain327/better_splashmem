<?php
function rename_lib_as_player_name($curr_name, $player_name, $nb_libs) {
    $target_dir = "player_libs/";
    $old = $target_dir . $curr_name;
    $new = $target_dir . $player_name . "v". $nb_libs . ".so";
    rename($old, $new);
    $data = explode("/", $new);
    return $data[1];
}