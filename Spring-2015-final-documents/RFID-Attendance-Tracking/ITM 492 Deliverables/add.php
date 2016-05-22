<html>
<body>

<?php
//Variables here are used to connect to SQL db
//Replace with credentials matching your own server
$servername = "localhost";
$username = "attendance";
$password = "itmt492";
$dbname = "ITMT492";

//$cardCode = $_POST['cardCode'];
$fname = $_POST['firstname'];
$lname = $_POST['lastname'];
$sid = $_POST['studentid'];

//Create connection
$connection = new mysqli($servername, $username, $password, $dbname);
//Check connection
if ($connection->connect_error) {
     die("Connection failed: " . $connection->connect_error);
} 

//Run query and check for results
$sql = "SELECT cardCode FROM TestTable ORDER BY id DESC LIMIT 1";
$result = $connection->query($sql);
$row = $result->fetch_assoc();
$cardCode = $row["cardCode"];

$sql = "INSERT INTO Students (cardCode, firstname, lastname, studentid)
		VALUES (" . $cardCode . ", " . "'" . $fname . "', " . "'" . $lname . "', " . "'" . $sid . "')";

//Check for success
if ($connection->query($sql) === TRUE) {
    echo "Record created successfully";

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