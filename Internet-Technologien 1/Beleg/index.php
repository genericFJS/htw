<!DOCTYPE html>
<html lang="de">
<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include_once 'php/Page.class.php';

$page = new Page ();
?>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title><?php $page->printTitle (); ?></title>

<?php include ('html/head.html'); ?>

<script src="script/script.js"></script>
</head>
<body>

	<div>
		<div class="ui-header ui-bar-a" data-form="ui-bar-a" data-role="header" role="banner">
			<a class="ui-btn-left ui-btn ui-btn-icon-notext ui-icon-home ui-btn-corner-all" title=" Home " data-form="ui-icon" href="?q=start"> Home </a>
			<img id="header-logo" alt="FJS" src="https://www.fj-strube.de/site/templates/media/FJS-logo_black.svg">
			<h1 class="ui-title" tabindex="0" role="heading" aria-level="1"><?php	$page->printTitle ();	?></h1>
		</div>

		<div class="ui-content ui-page-theme-a" data-form="ui-page-theme-a" role="main">
			<?php $page->printMainContent (); ?>
		</div>

		<div data-role="footer">
			<div data-role="navbar">
    		<?php $page->printFooterContent (); ?>
    	</div>
		</div>

		<div id="debug"><?php echo $page->debug;?></div>
	</div>

</body>

</html>
