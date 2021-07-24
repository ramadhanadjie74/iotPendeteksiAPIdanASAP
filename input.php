<?php
    include('koneksi.php');

    $sensor = $_GET['sensor'];
    $lokasi = $_GET['lokasi'];
    $ip = $_GET['ip'];
    $status = $_GET['status'];

    $input = mysqli_query($koneksi, "INSERT INTO data (sensor, lokasi, ip, status) VALUES ('$sensor', '$lokasi', '$ip', '$status') ");
    if($input == TRUE){
        echo "Berhasil Input";
    }else{
        echo "Gagal Input";
    }

?>