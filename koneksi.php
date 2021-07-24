<?php
    $server = "localhost";
    $username = "root";
    $password = "";
    $database = "flame";

    $koneksi = mysqli_connect($server, $username, $password, $database);
    if($koneksi == TRUE){
        // echo "Terhubung";
    }else{
        echo "Tidak Terhubung";
    }
?>