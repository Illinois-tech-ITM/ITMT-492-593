<html>
<body>

<?php
//This script is called every time the Arduino registers a valid scan

//Variables here are used to connect to SQL db
//Replace with credentials matching your own server
$servername = "localhost";
$username = "attendance";
$password = "itmt492";
$dbname = "ITMT492";
//$num is the data posted from the Ardunino
$num = $_POST["cardCode"];
$test = "45";

// Create connection
$connection = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($connection->connect_error) {
     die("Connection failed: " . $connection->connect_error);
} 

//Run SQL
$sql = "INSERT INTO TestTable (cardCode)
		VALUES (" . $_POST["data"] . ")";
$connection->query($sql);

$connection->close();

?>

</body>
</html>