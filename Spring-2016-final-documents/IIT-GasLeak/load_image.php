<!DOCTYPE html>
<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url");  // Refresh the webpage every 5 seconds
?> 
<html>
<head>
<h2>Perlstein Hall</h2>
 
<canvas id="myCanvas" width="1000" height="500"></canvas>
<script type="text/javascript">

    var c = document.getElementById("myCanvas");
    var ctx = c.getContext("2d");

    var image = new Image();
	//var sensorValue=100;
    image.onload = function () {
        ctx.drawImage(image, 1, 1);
		
		//draw a circle
        ctx.beginPath();
        ctx.arc(400, 225, 25, 0, Math.PI * 2, true);
		setColor();
        ctx.stroke();
		//draw a circle
        ctx.beginPath();
        ctx.arc(400, 400, 25, 0, Math.PI * 2, true);
		ctx.fillStyle = 'rgb(0, 204, 0)';
		ctx.fill();
        ctx.stroke();
		//draw a circle
        ctx.beginPath();
        ctx.arc(450, 260, 25, 0, Math.PI * 2, true);
		ctx.fillStyle = 'rgb(0, 204, 0)';
		ctx.fill();
        ctx.stroke();
		//draw a circle
        ctx.beginPath();
        ctx.arc(450, 380, 25, 0, Math.PI * 2, true);
		ctx.fillStyle = 'rgb(0, 204, 0)';
		ctx.fill();
        ctx.stroke();
     };
	 
	 function setColor(){
		 if(<?php
$row = 1;
if (($handle = fopen("test.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1024, ",")) !== FALSE) {
        $num = count($data);
        $row++;
        for ($c=0; $c < $num; $c++) {
            echo($data[$c]);
			//echo(0);
        }
		//echo( $data[4]);
    }
    fclose($handle);
}
?><=157){
			ctx.fillStyle = 'rgb(0, 204, 0)';
			ctx.fill();
		 }
		else{
			ctx.fillStyle = "red";
			ctx.fill();
		}
		 
	 }

    image.src = 'Perlstein_Hall.jpg';                 
  
</script>
</head>
 

</body>
</html>