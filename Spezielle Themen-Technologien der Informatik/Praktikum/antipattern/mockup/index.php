<!DOCTYPE html>
<html lang="de">
<?php
// Erzeuge die Verwaltung für den Seiteninhalt:
include_once 'page.class.php';
$page = new Page ();
?>
<head>
	<!-- Binde die Stylesheet- und Javascript-Datei ein: -->
	<link rel="stylesheet" href="style.css" />
	<script src="script.js"></script>
</head>
<body>
	<?php
	// Generiere Inhalt des Headers:
	$page->printHeader();
	?>
		<main>
			<?php
			// Generiere Main-Seiteninhalt:
			$page->printMainContent ();
			?>
		</main>
<?php
	// Generiere Inhalt des Footers:
	$page->printFooter();
	?>
</body>

</html>