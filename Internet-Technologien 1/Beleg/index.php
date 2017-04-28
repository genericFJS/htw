<!DOCTYPE html>
<html lang="de">
<!-- <?php include('functions.php');?> -->
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<title>Vokabeltrainer</title>
	<meta name="description" content="Beleg Internet-Technologien 1 an der HTW Dresden von Falk-Jonatan Strube (s74053)." />
	<meta name="keywords" content="genericFJS, FJS, fj-strube, Falk-Jonatan, Strube, s74053, it1, beleg">
	<meta name="author" content="Falk-Jonatan Strube (genericFJS)">
	<!-- favicons -->
	<link rel="apple-touch-icon" sizes="57x57" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-57x57.png">
	<link rel="apple-touch-icon" sizes="60x60" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-60x60.png">
	<link rel="apple-touch-icon" sizes="72x72" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-72x72.png">
	<link rel="apple-touch-icon" sizes="76x76" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-76x76.png">
	<link rel="apple-touch-icon" sizes="114x114" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-114x114.png">
	<link rel="apple-touch-icon" sizes="120x120" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-120x120.png">
	<link rel="apple-touch-icon" sizes="144x144" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-144x144.png">
	<link rel="apple-touch-icon" sizes="152x152" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-152x152.png">
	<link rel="apple-touch-icon" sizes="180x180" href="http://www.fj-strube.de/site/templates/fav/apple-touch-icon-180x180.png">
	<link rel="icon" type="image/png" href="http://www.fj-strube.de/site/templates/fav/favicon-194x194.png" sizes="194x194">
	<link rel="icon" type="image/png" href="http://www.fj-strube.de/site/templates/fav/android-chrome-192x192.png" sizes="192x192">
	<link rel="icon" type="image/png" href="http://www.fj-strube.de/site/templates/fav/favicon-96x96.png" sizes="96x96">
	<link rel="icon" type="image/png" href="http://www.fj-strube.de/site/templates/fav/favicon-32x32.png" sizes="32x32">
	<link rel="icon" type="image/png" href="http://www.fj-strube.de/site/templates/fav/favicon-16x16.png" sizes="16x16">
	<link rel="manifest" href="http://www.fj-strube.de/site/templates/fav/manifest.json">
	<link rel="mask-icon" href="http://www.fj-strube.de/site/templates/fav/safari-pinned-tab.svg" color="#485030">
	<link rel="shortcut icon" href="http://www.fj-strube.de/favicon.ico">
	<meta name="msapplication-TileColor" content="#485030">
	<meta name="msapplication-TileImage" content="http://www.fj-strube.de/site/templates/fav/mstile-144x144.png">
	<meta name="msapplication-config" content="http://www.fj-strube.de/site/templates/fav/browserconfig.xml">
	<meta name="theme-color" content="#dee2cf">
	<!-- style sheets -->
	<link rel="stylesheet" media="screen" href="https://fontlibrary.org/face/nimbus-sans-l" type="text/css" />
	<link rel="stylesheet" href="font-awesome/css/font-awesome.min.css">
	<link rel="stylesheet" type="text/css" href="styles/style-norm.css">
	<link rel="stylesheet" type="text/css" href="styles/main.css">

	<!-- jQuery mobile -->
	<!-- Include meta tag to ensure proper rendering and touch zooming -->
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<!-- Include jQuery Mobile stylesheets (or not) -->
	<!--	<link rel="stylesheet" href="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css">-->
	<link rel="stylesheet" href="styles/mobile-work.css">
	<!-- Include the jQuery library -->
	<script src="https://code.jquery.com/jquery-1.11.3.min.js"></script>
	<!-- Include the jQuery Mobile library -->
	<script src="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
	<script src="script/script.js"></script>
</head>
	<body class="">

		<!-- language switcher / navigation -->
		<header id="header">
		</header>

		<div class="hblock">
			<img alt="FJS Logo" src="http://www.fj-strube.de/site/templates/media/logo-entwurf3c_tinted.svg">
			<h2>Lektion</h2>
		</div>


		<div id='main'>
			<!-- main content -->
			<div id="content">
				<?php getContent(); ?>
					<?php if(isset($_GET['q'])) {
			switch ($_GET['q']){
	// get Vokabel
	//--------------------------------
			case 'voc':
				// wenn eine l richtig gesetzt wurde…
				if(isset($_GET['l'])){ 
					$lectionfile = "lections/".$_GET['l'].".csv";
					// … und die datei existiert:
					if(file_exists($lectionfile)){
					$handle = @fopen($lectionfile, "r");
					if ($handle) {
						// lese eine zufällige zeile aus datei aus
						$totalrows = 0;
						while (($buffer = fgets($handle, 4096)) !== false) {
							$totalrows++;
						}
						$randomrows = UniqueRandomNumbersWithinRange(0,$totalrows-1,6);
						$totalrow = 0;
						rewind($handle);
						$selset = 0;
						while (($buffer = fgets($handle, 4096)) !== false && $selset < 5) {
							$tmp = str_getcsv($buffer, "	");
							switch ($totalrow){
								case $randomrows[0]:
									$voc = $tmp[0];
									$ipa = $tmp[1];
									$sel[0] = $tmp[2];
									$selset++;
									break;
								case $randomrows[1]:
									$sel[1] = $tmp[2];
									$selset++;
									break;
								case $randomrows[2]:
									$sel[2] = $tmp[2];
									$selset++;
									break;
								case $randomrows[3]:
									$sel[3] = $tmp[2];
									$selset++;
									break;
								case $randomrows[4]:
									$sel[4] = $tmp[2];
									$selset++;
									break;
							}
							$totalrow++;
						}
						fclose($handle);
					}
			
			
			?>
						<div id='direction'>
							<div class='current'><a href=''>A <i class="fa fa-arrow-right fa-1" aria-hidden="true"></i> B</a></div>
							<div><a href=''>A <i class="fa fa-arrow-left" aria-hidden="true"></i> B</a></div>
						</div>
						<form action="">
							<div class="voc spa">
								<?php echo "<p>".$voc."</p><p>".$ipa."</p>"; ?>
							</div>
							<div class="voc spchoice">
								<?php
							foreach($sel as $choice){
								echo "<input type='radio' name='gender' value='male'>".$choice."<br>";
							}
						?>
							</div>
							<input type="submit">Abschicken</input>
						</form>
						<?php } else { ?>
							<div class="notify">Die ausgewählte Lektion (
								<?php echo $_GET['l'] ?>) existiert nicht!</div>
							<?php }} else { ?>
								<div class="notify">Es wurde keine Lektion ausgewählt!</div>
								<?php } ?>
									<?php
			break;
			}}?>
			</div>
		</div>

		<!-- footer -->
		<div class="hblock">
			<footer id='footer'>
				<nav>
					<ul class='topnav'>
						<?php if(!isset($_GET['q']) ||(isset($_GET['q']) && !(strcmp($_GET['q'],"sel") == 0 ) )){?>
							<li class="three"><a href='?q=sel'>Auswahl</a></li>
							<?php } 
					if(!isset($_GET['q']) ||(isset($_GET['q']) && !(strcmp($_GET['q'],"stat") == 0) )){?>
								<li class="three"><a href='?q=stat'>Statistik</a></li>
								<?php } 
					if(!isset($_GET['q']) ||(isset($_GET['q']) && !(strcmp($_GET['q'],"setup") == 0) )){?>
									<li class="three"><a href='?q=setup'>Setup</a></li>
									<?php }?>
					</ul>
				</nav>
			</footer>
		</div>

		<div id="debug">
		</div>

	</body>

</html>
