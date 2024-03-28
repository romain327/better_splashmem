<?php
function rename_lib_as_player_name($curr_name, $player_name) {
    $target_dir = "player_libs/";
    $old = $target_dir . $curr_name . ".c";
    $new = $target_dir . $player_name . ".c";
    rename($old, $new);
}