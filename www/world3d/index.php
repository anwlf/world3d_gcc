<?
    $base = "";
    $key = "";
    $concat = "?";
    if (isset($_REQUEST['base'])) {
	$base=$_REQUEST['base'];
	$base_url="?base=".$_REQUEST['base'];
	if (isset($_REQUEST['key'])) {
	    $key=$_REQUEST['key'];
	    $key_url="&key=".$_REQUEST['key'];
	}
	$concat="&";
    }
?>
<!DOCTYPE html>
<html>
<head>
<style>
a:link {color:#FFFFFF;}      /* unvisited link */
a:visited {color:#00FF00;}  /* visited link */
a:hover {color:#FF00FF;}  /* mouse over link */
a:active {color:#0000FF;}  /* selected link */ 
body_
{
    background:url("/images/night_sky_large.jpg");
    background-size:cover;
    background-repeat:repeat;
    box-align:center;
}
body_
{
    background:url("/images/stars-blue.jpg");
    background-repeat:repeat;
}
body
{
    background-color:#00001F;
}
div
{
    margin:auto;
}
img
{
    position:absolute;
    top:35px;
    width:80%;
    left:10%;
    right:10%;
}
.panel
{
    position:absolute;
    width:80%;
    left:10%;
    right:10%;
    top_:89%;
    bottom:5%;
    text-align:center;
}
.center
{
    position:absolute;
    width:80%;
    left:10%;
    right:10%;
    background-color:#b0e0e6;
}

</style>
<script type="text/javascript">
function refresh()
{
    var d = new Date();
    var m = Math.floor(d.getMilliseconds()/10);
    var pic_ = "./image.php<?echo $base_url.$concat;?>";
		
    document.images["pic"].src=pic_ + "time=" + d + "&mils=" +m;
    setTimeout("refresh();",500);
}
//if (document.images)  window.onload = refresh;
</script>
<title>World3D</title>
</head> 
<body onload="refresh();">
<div class="center"><b>World3D</b></div>
<div>
<!img src="/images/night_sky_large.jpg" style="{z-index:-1;}"></img>
<!img src="/images/pic3.jpg" style="{z-index:-1;}"></img>
<img src="./image.php<?echo $base_url.$key_url;?>" id="pic" style="{z-index:1;} onload_="refresh();" onerror_="refresh();"></img>
<!img src="/images/w3d.png" id="pic" style="{z-index:1;} onload_="refresh();" onerror_="refresh();"></img>
</div>
<?
    if (isset($_REQUEST['base'])) {
	echo "<p class=\"panel\"><b>Base ".$base."</b></br><a href=\"./index.php?escape=".$base."\">Escape</a>&nbsp;<a href=\"index.php?base=".$base."&key=0\">Reset</a></p>";
	echo "<table class=\"panel\"><tr><td><a href=\"index.php?base=".$base."&key=2\">Clock Wise</a></td>";
	echo "<td><a href=\"index.php?base=".$base."&key=3\">Counter Clock Wise</a></td></tr>";
	echo "<tr><td><a href=\"index.php?base=".$base."&key=4\">Left</a></td>";
	echo "<td><a href=\"index.php?base=".$base."&key=6\">Right</a></td></tr>";
	echo "<tr><td><a href=\"index.php?base=".$base."&key=5\">Up</a></td>";
	echo "<td><a href=\"index.php?base=".$base."&key=7\">Down</a></td></tr>";
	echo "<tr><td><a href=\"index.php?base=".$base."&key=8\">Speed Up</a></td>";
	echo "<td><a href=\"index.php?base=".$base."&key=9\">Speed Down</a></td></tr></table>";
//	echo "<p class=\"panel\"><a href=\"index.php?base=".$base."&key=0\">Reset</a></p>";
    } else {
	echo "<p class=\"panel\">";
	$escape ="";
	if (isset($_REQUEST['escape'])) {
	    $escape = $_REQUEST['escape'];
	}
	if ((!file_exists("../../var/base0.txt")) || ($escape == "0")) {
	    echo "<a href=\"./index.php?base=0\">Base 0</a>&nbsp;&nbsp;";
	}
	if ((!file_exists("../../var/base1.txt")) || ($escape == "1")) {
	    echo "<a href=\"./index.php?base=1\">Base 1</a>&nbsp;&nbsp;";
	}
	if ((!file_exists("../../var/base2.txt")) || ($escape == "2")) {
	    echo "<a href=\"./index.php?base=2\">Base 2</a>";
	}
	echo "</p>";
    }
?>
</body>
</html>