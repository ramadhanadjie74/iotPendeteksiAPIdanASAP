<?php header("refresh: 3"); ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <?php include('desain.php'); ?>
    <?php include('koneksi.php'); ?>
</head>

<?php

    $dataAsap = mysqli_query($koneksi, "SELECT * FROM data WHERE sensor='Sensor Asap' ORDER BY no DESC LIMIT 1 ");
    $row1 = mysqli_fetch_array($dataAsap);
    $namaAsap = $row1['sensor'];
    $lokasiAsap = $row1['lokasi'];
    $ipAsap= $row1['ip'];
    $statusAsap = $row1['status'];

    $dataApi = mysqli_query($koneksi, "SELECT * FROM data WHERE sensor='Flame Sensor' ORDER BY no DESC LIMIT 1 ");
    $row2 = mysqli_fetch_array($dataApi);
    $namaApi = $row2['sensor'];
    $lokasiApi = $row2['lokasi'];
    $ipApi= $row2['ip'];
    $statusApi = $row2['status'];
    
?>

<body>
    <div class="container">

    <br>

    <h1> FLAME EARLY WARNING </H1>

        <table class="table table-bordered">
            <thead>
                <tr>
                    <th scope="col">No</th>
                    <th scope="col">Nama Sensor</th>
                    <th scope="col">Lokasi</th>
                    <th scope="col">IP</th>
                    <th scope="col">Status</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <th scope="row">1</th>
                    <td><?php echo $namaApi; ?></td>
                    <td><?php echo $lokasiApi; ?></td>
                    <td><?php echo $ipApi; ?></td>

                    <td><?php if($statusApi == "Tidak Ada Api"){ ?>
                        <p class="text-success"><?php echo $statusApi; ?></p>
                        <?php } else{ ?>
                        <p class="text-danger"><?php echo $statusApi; ?></p>
                        <?php }?>
                    </td>

                </tr>
                <tr>
                    <th scope="row">2</th>
                    <td><?php echo $namaAsap; ?></td>
                    <td><?php echo $lokasiAsap; ?></td>
                    <td><?php echo $ipAsap; ?></td>
                    <td><?php if($statusAsap == "Tidak Ada Asap"){ ?>
                        <p class="text-success"><?php echo $statusAsap; ?></p>
                        <?php } else{ ?>
                        <p class="text-danger"><?php echo $statusAsap; ?></p>
                        <?php }?>
                    </td>
                </tr>
            </tbody>
        </table>


    </diV>
</body>
</html>