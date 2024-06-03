<?php
error_reporting(E_ALL);
require_once("functions.php");
$html =file_get_contents("html/account.html");
$css = file_get_contents("css/light.css");

session_start();

$html = change_mode($html, "[css]", $_SESSION["mode"], "[icon]", $_SESSION["icon"], "[background]", $_SESSION["background"]);

$color = file_get_contents("database/color.csv");
$color = str_replace("\n", "", $color);
$new_color = get_color($_SESSION["mode"]);
$css = str_replace($color, $new_color, $css);
file_put_contents("css/light.css", $css);
file_put_contents("database/color.csv", $new_color);

$old_name = $_SESSION["name"];
$name = "";
$password = "";
if(isset($_POST["name"])) {
    $file = file_get_contents("database/user.csv");
    if(strpos($file, $_POST["name"]) !== false) {
        $html = str_replace("<!--[login_error_create]-->", "<p>Ce nom d'utilisateur est déjà pris.</p>", $html);
    }
    else {
        $name = $_POST["name"];
    }
}

if(isset($_POST["password"]) && isset($_POST["password2"])) {
    if (sha1($_POST["password"]) != sha1($_POST["password2"])) {
        $html = str_replace("<!--[login_error_create]-->", "<p>Les mots de passe ne correspondent pas.</p>", $html);
    } else {
        $password = sha1($_POST["password"]);
    }
}
if($name != "") {
    $file = file_get_contents("database/user.csv");
    foreach (explode("\n", $file) as $line) {
        $data = explode(";", $line);
        if($data[0] == $old_name) {
            $data[0] = $name;
            $data[1] = $password;
            $line = implode(";", $data);
        }
    }
    file_put_contents("database/user.csv", $file);
    $_SESSION["name"] = $name;
}
if($password != "") {
    $file = file_get_contents("database/user.csv");
    foreach (explode("\n", $file) as $line) {
        $data = explode(";", $line);
        if($data[0] == $name) {
            $data[1] = $password;
            $line = implode(";", $data);
        }
    }
    file_put_contents("database/user.csv", $file);
    $file = file_get_contents("database/score.csv");
    foreach (explode("\n", $file) as $line) {
        $data = explode(";", $line);
        if($data[0] == $old_name) {
            $data[0] = $name;
            $line = implode(";", $data);
        }
    }
    file_put_contents("database/score.csv", $file);
}

$file = fopen("database/score.csv", "r");
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