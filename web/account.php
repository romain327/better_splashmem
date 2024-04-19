<?php
error_reporting(E_ALL);
require_once("functions.php");
$html = file_get_contents("html/account.html");
$css = file_get_contents("css/colors.css");

session_start();

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color();
$css = str_replace($color, $new_color, $css);
file_put_contents("css/colors.css", $css);
file_put_contents("database/color.csv", $new_color);

if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] . "</p>", $html);
    $html = str_replace("<!--[logout]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
}

if($_POST) {
    $file = file_get_contents("database/libs.csv");
    $lines = explode("\n", $file);
    foreach($_POST as $key => $value) {
        foreach ($lines as $line) {
            $data = explode(";", $line);
            if($data[1] == $value && $data[0] == $_SESSION["name"]) {
                unlink("player_libs/" . $data[1]);
                unset($lines[array_search($line, $lines)]);
            }
        }
    }
    $file = implode("\n", $lines);
    file_put_contents("database/libs.csv", $file);
    $_SESSION["libs"] = refresh_lib_version($_SESSION["name"])-1;
    $html = str_replace("<!--[libs_msg]-->", "<p>Librairies supprimées.</p>", $html);
}

$file = fopen("database/libs.csv", "r");
$nb_libs = 0;
while(!feof($file)) {
    $line = fgets($file);
    $line = explode(";", $line);
    if($line[0] == $_SESSION["name"]) {
        $libs[$line[1]] = $line[0];
        $nb_libs++;
    }
}
fclose($file);
$html_libs = "";
$lib_count = 1;
while($lib_count <= $nb_libs) {
    $html_libs .= "<div class='check_lib'><input type='checkbox' name='lib" . $lib_count ."' value='" . key($libs) . "'><label>" . key($libs) . "</label></div>";
    next($libs);
    $lib_count++;
}
$html = str_replace("<!--[libs]-->", $html_libs, $html);
echo $html;