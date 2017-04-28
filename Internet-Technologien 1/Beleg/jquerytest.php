<!DOCTYPE html>
<html lang="de">

<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<title>jQuery TEST</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css">
	<script src="https://code.jquery.com/jquery-1.11.3.min.js"></script>
	<script src="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
	<script>
		function test() {
			// es soll auf der aktuellen Seite die aktuelle Seitenbreite und die aktuelle Überschrift erscheinen
			var $testS = "jquery loaded on page: " + $("#heading", $.mobile.activePage).html() + "<br>" + "Seitenbreite: " + $(window, $.mobile.activePage).innerWidth()+ ", Breite von #debug: " +$("#debug", $.mobile.activePage).width();
			//$("#debug").html($testS);
			$("#debug", $.mobile.activePage).html($testS);
		}

		// load, resize: normales jQuery (funktioniert für erste Seite)
		// pageinit/pageload/...: jQuery mobile FUNKTIONIERT NICHT
		// ich erwarte: auf jeder seite wird die aktuelle Breite und Überschrift angezeigt
		// was passiert: nur auf der ersten Seite wird die Breite und Überschrift angezeigt, beim verändern der Fenstergröße werden die angezeigten Breiten-Werte auch nur auf der ersten Seite geändert.
		$(window).on("resize pageshow", test);

	</script>
</head>

<body>
	<h1 id="heading">
	<?php
		if(isset($_GET['a'])) {
			echo "Seite A";
		} else if(isset($_GET['b'])) {
			echo "Seite B";
		} else {
			echo "Keine Seite";
		}
	?>	
	</h1>

	<p><a href='?a'>seite a</a></p>
	<p><a href='?b'>seite b</a></p>
	<div id="debug" style="width: 50%; padding: 5px; background: white;"></div>
</body>

</html>
