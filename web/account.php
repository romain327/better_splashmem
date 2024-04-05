<?php
error_reporting(E_ALL);
$html = file_get_contents("html/account.html");

session_start();
if(isset($_SESSION["name"])) {
    $html = str_replace("<!--[name]-->", "<p>" . $_SESSION["name"] . "</p>", $html);
    $html = str_replace("<!--[logout]-->", '<a class="menu_link" href="logout.php">Déconnexion</a>', $html);
}

if($_POST) {
    $file = file_get_contents("database/score.csv");
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