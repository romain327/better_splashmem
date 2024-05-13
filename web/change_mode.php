<?php
error_reporting(E_ALL);

session_start();
$_SESSION["change_mode"] = 1;

if(isset($_GET["page"])) {
    if($_GET["page"] == 5) {
        header("Location: account.php");
    }
    else if($_GET["page"] == 4) {
        header("Location: install.php");
    }
    else if($_GET["page"] == 3) {
        header("Location: rules.php");
    }
    else if($_GET["page"] == 2) {
        header("Location: ranking.php");
    }
    else {
        header("Location: index.php");
    }
}