<?php

    // Prepare variables for database connection
   
    $dbusername = "3044165_arduino";  // enter database username, I used "arduino" in step 2.2
    $dbpassword = "Fortytwo42";  // enter database password, I used "arduinotest" in step 2.2
    $server = "fdb25.runhosting.com"; // IMPORTANT: if you are using XAMPP enter "localhost", but if you have an online website enter its address, ie."www.yourwebsite.com"

    // Connect to your database

    $dbconnect = mysqli_pconnect($server, $dbusername, $dbpassword);
    $dbselect = mysqli_select_db("3044165_arduino",$dbconnect);

    // Prepare the SQL statement

   // $sql = "INSERT INTO b14_23898070_sensordata.lightsensor (value) VALUES ('phpTEST')";    
   $sql = "INSERT INTO 3044165_arduino.lightsensor (value) VALUES ('".$_GET["value"]."')";   

    // Execute SQL statement

    mysqli_query($sql);

?>