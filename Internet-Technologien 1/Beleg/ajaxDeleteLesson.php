<?php
// lösche Datei und gib aus, ob das Löschen erfolgreich war
if (unlink ( $_GET ["f"] ))
	echo "true";
else 
	echo "false";
?>