<html>
<?php
$page = $_SERVER['PHP_SELF'];
$sec = "2.5";
?>
<head>
	<!-- Updates scan table -->
	<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
<body>

<!-- Page container setup -->
<!-- Styles are in-line; External CSS stylesheets can be applied as per standard implementation in the HTML header -->
<table width="580"><tr><td width="350"><b>Name</b></td><td width="200"><b>Student ID</b></td><td width="175"><b>Time Scanned In</b></td></tr></table>
<div style="width:600px;height:30em;overflow:auto">
<?php
//Variables here are used to connect to SQL db
//Replace with credentials matching your own server
$servername = "localhost";
$username = "attendance";
$password = "itmt492";
$dbname = "ITMT492";

//Create connection
$connection = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($connection->connect_error) {
     die("Connection failed: " . $connection->connect_error);
} 

//Run query
$sql = "SELECT firstname, lastname, studentid, DATE_SUB(scantime, INTERVAL 5 HOUR) AS cstscan FROM Students INNER JOIN TestTable ON Students.cardCode=TestTable.cardCode ORDER BY TestTable.scantime DESC";
$result = $connection->query($sql);

//Parse results and display them
if ($result->num_rows > 0) {
	echo "<table width=\"580\">";
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<tr><td width=\"200\">" . $row["firstname"]. " " . $row["lastname"]. "</td><td width=\"50\">" . "&nbsp" . "</td><td>" . $row["studentid"] . "</td><td width=\"50\">" . "&nbsp" . "</td><td>" . $row["cstscan"] . "</td></tr>";
    }
	echo "</table>";
} else {
    echo "0 results";
}

$connection->close();
?>
</div>
<br />
<button onclick="window.location='add.html'">Add New Student</button>
<button onclick="window.location='delete.html'">Delete Student</button>
<button onclick="window.location='viewbytime.html'">Filter Results</button>
<button onclick="window.location='search.html'">Search by ID</button>

<!-- Allows the back button to navigate backwards -->
<script>
function goBack() {
	window.history.back();
	}
</script>

</body>
</html>