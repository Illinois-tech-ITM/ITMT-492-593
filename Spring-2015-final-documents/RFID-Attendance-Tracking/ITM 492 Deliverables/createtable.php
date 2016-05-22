<html>
<body>

<?php
//WARNING
//This script is only to demonstrate how to set up a new table. It is not a part of runtime.

//Variables here are used to connect to SQL db
//Replace with credentials matching your own server
$servername = "localhost";
$username = "james";
$password = "changeme123";
$dbname = "ITMT492";

// Create connection
$connection = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($connection->connect_error) {
     die("Connection failed: " . $connection->connect_error);
} 

//Define the table
$sql = "CREATE TABLE Students (
id INT(5) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
cardCode INT(5) NOT NULL,
firstname VARCHAR(15) NOT NULL,
lastname VARCHAR(15) NOT NULL,
studentid VARCHAR(9) NOT NULL
)";

//Run query and check for success
if ($connection->query($sql) === TRUE) {
    echo "Table Created";
} else {
    echo "Error creating table: " . $connection->error;
}

$connection->close();
?>

</body>
</html>