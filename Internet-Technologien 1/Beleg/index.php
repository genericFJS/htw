<!DOCTYPE html>
<html lang="de">
<?php

// zeige alle php-Fehlermeldungen an (zum Debuggen)
ini_set ( 'display_errors', 1 );
ini_set ( 'display_startup_errors', 1 );
error_reporting ( E_ALL );

// erzeuge die Verwaltung für den Seiteninhalt
include_once 'php/Page.class.php';
$page = new Page ();
?>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title><?php $page->printTitle (); ?></title>

<?php
// Füge die Kopfzeile mit statischen Metadaten, Styles und Scripten ein (head.html).
include ('html/head.html');
?>

</head>
<body>

	<div>
		<header class="ui-header ui-bar-a" data-form="ui-bar-a" data-role="header" role="banner">
			<a class="ui-btn-left ui-btn ui-btn-icon-notext ui-icon-home ui-btn-corner-all" title=" Home " data-form="ui-icon" href="?q=start"> Home </a> <img id="header-logo" alt="FJS" src="https://www.fj-strube.de/site/templates/media/FJS-logo_black.svg">
			<h1 class="ui-title" tabindex="0" role="heading" aria-level="1"><?php	$page->printTitle ();	?></h1>
		</header>

		<main id="mainContent" class="ui-content ui-page-theme-a" data-form="ui-page-theme-a" role="main">
			<?php
			// zeige Seiteninhalt an
			$page->printMainContent ();
			?>
		</main>

		<footer data-role="footer">
			<div id="footerContent" data-role="navbar">
    		<?php
						// zeige Fußzeile an
						$page->printFooterContent ();
						?>
    	</div>
		</footer>

		<div id="debug"><?php echo $page->debug;?></div>
	</div>

</body>

</html>
