<?php
error_reporting(E_ALL);

$conn = mysqli_connect("localhost", "root", "", "better_splashmem");
if(!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

mysqli_set_charset($conn, "utf8");