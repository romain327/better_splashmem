<?php
function rename_lib_as_player_name($curr_name, $player_name, $nb_libs) {
    $target_dir = "player_libs/";
    $old = $target_dir . $curr_name . ".so";
    $new = $target_dir . $player_name . "_". $nb_libs . ".so";
    rename($old, $new);
    $data = explode("/", $new);
    return $data[1];
}

function get_date() {
    return date("Y-m-d");
}

function logout() {
    if($_SESSION["user"] == 0) {
        $file = file_get_contents("database/user.csv");
        $lines = explode("\n", $file);
        foreach ($lines as $key => $line) {
            $data = explode(";", $line);
            if($data[0] == $_SESSION["name"]) {
                unset($lines[$key]);
            }
        }
        $file = implode("\n", $lines);
        file_put_contents("database/user.csv", $file);

        $file = file_get_contents("database/score.csv");
        $lines = explode("\n", $file);
        foreach ($lines as $key => $line) {
            $data = explode(";", $line);
            if($data[0] == $_SESSION["name"]) {
                unset($lines[$key]);
                unlink("player_libs/" . $data[1]);
            }
        }
        $file = implode("\n", $lines);
        file_put_contents("database/score.csv", $file);
    }
    session_destroy();
}

function get_lib_version($lib_name) {
    $data = explode("_", $lib_name);
    $data = explode(".", $data[1]);
    return $data[0];
}

function get_libs_versions($pseudo) {
    $file = file_get_contents("database/libs.csv");
    $lines = explode("\n", $file);
    $versions = array();
    foreach ($lines as $line) {
        $data = explode(";", $line);
        if($data[0] == $pseudo) {
            $versions[] = get_lib_version($data[1]);
        }
    }
    return $versions;
}

function refresh_lib_version($pseudo) {
    $versions = get_libs_versions($pseudo);
    $version = 1;
    while(in_array($version, $versions)) {
        $version++;
    }
    return $version;
}

function check_lib_exists($pseudo, $version) {
    $file = file_get_contents("database/libs.csv");
    $lines = explode("\n", $file);
    foreach ($lines as $line) {
        $data = explode(";", $line);
        if($data[0] == $pseudo && get_lib_version($data[1]) == $version) {
            return true;
        }
    }
    return false;
}
function overwrite_lib_version($pseudo) {
    $version = refresh_lib_version($pseudo);
    $lines = file_get_contents("database/user.csv");
    $lines = explode("\n", $lines);
    foreach ($lines as $key => $line) {
        $data = explode(";", $line);
        if($data[0] == $pseudo) {
            $data[2] = $version;
            $lines[$key] = implode(";", $data);
        }
    }
    $lines = implode("\n", $lines);
    file_put_contents("database/user.csv", $lines);
}

function get_color() {
    $colors = array("00ff7f", "00ffff", "ee82ee", "5d11f3");
    $len = count($colors);
    $color = $colors[rand(0, $len - 1)];
    return $color;
}