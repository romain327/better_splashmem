<?php
error_reporting(E_ALL);

if ($_SERVER['REQUEST_METHOD'] == 'PUT') {
    $path = 'tmp.csv';

    $file = fopen($path, 'w');

    if ($file) {
        $data = file_get_contents('php://input', 'r');
        fwrite($file, $data);
        fclose($file);

        http_response_code(200);
        echo "Fichier reçu avec succès.";

        $file = fopen('database/score.csv', 'a');

        $data = file_get_contents($path);
        $datas = explode("\n", $data);
        $master = $datas[0];
        foreach ($datas as $line) {
            $line = explode(";", $line);
            $dt = $line[0] . ";" . $line[1] . ";" . $line[2] . ";" . $master . "\n";
            fwrite($file, $dt);
        }

        fclose($file);
        //unset($file);
    } else {
        http_response_code(500);
        echo "Erreur lors de l'ouverture du fichier.";
    }
} else {
    http_response_code(405);
    echo "Méthode non autorisée.";
}
