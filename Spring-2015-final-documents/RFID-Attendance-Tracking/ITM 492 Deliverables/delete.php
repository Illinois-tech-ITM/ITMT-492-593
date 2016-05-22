<html>
<body>

<?php
//Variables here are used to connect to SQL db
//Replace with credentials matching your own server
$servername = "localhost";
$username = "attendance";
$password = "itmt492";
$dbname = "ITMT492";

$code = $_POST['idcode'];

// Create connection
$connection = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($connection->connect_error) {
     die("Connection failed: " . $connection->connect_error);
} 

//Run query
$sql = "DELETE FROM Students WHERE studentid=" . $code;

//Check for success
if ($connection->query($sql) === TRUE) {
    echo "Record deleted successfully";

} else {
    echo "Error: " . $sql . "<br>" . $connection->error;
}

$connection->close();
?>
<br />
<button onclick="window.location='add.html'">Add Another Student</button>
<br />
<button onclick="window.location='index.php'">Back to Overview</button>

</body>
</html>