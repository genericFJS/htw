<?php
// globale Variablen:
$voc;
$ipa;
$sel;
$selorder;

// aus: https://stackoverflow.com/a/5612704
/**
 *
 * @param unknown $min        	
 * @param unknown $max        	
 * @param unknown $quantity        	
 * @return array
 */
function UniqueRandomNumbersWithinRange($min, $max, $quantity) {
	$numbers = range ( $min, $max );
	shuffle ( $numbers );
	return array_slice ( $numbers, 0, $quantity );
}

// hole zufällige Vokabeln aus entsprechender Datei
function getVocabulary($fileName) {
	$lectionfile = "lections/" . $fileName . ".csv";
	if (file_exists ( $lectionfile )) {
		$handle = @fopen ( $lectionfile, "r" );
		if ($handle) {
			// lese eine zufällige zeile aus datei aus
			$totalrows = 0;
			while ( ($buffer = fgets ( $handle, 4096 )) !== false ) {
				$totalrows ++;
			}
			$randomrows = UniqueRandomNumbersWithinRange ( 0, $totalrows - 1, 6 );
			$totalrow = 0;
			rewind ( $handle );
			$selset = 0;
			while ( ($buffer = fgets ( $handle, 4096 )) !== false && $selset < 5 ) {
				$tmp = str_getcsv ( $buffer, "	" );
				switch ($totalrow) {
					case $randomrows [0] :
						$voc = $tmp [0];
						$ipa = $tmp [1];
						$sel [0] = $tmp [2];
						$selset ++;
						break;
					case $randomrows [1] :
						$sel [1] = $tmp [2];
						$selset ++;
						break;
					case $randomrows [2] :
						$sel [2] = $tmp [2];
						$selset ++;
						break;
					case $randomrows [3] :
						$sel [3] = $tmp [2];
						$selset ++;
						break;
					case $randomrows [4] :
						$sel [4] = $tmp [2];
						$selset ++;
						break;
				}
				$totalrow ++;
			}
			fclose ( $handle );
		}
		return true;
	} else {
		return false;
	}
}
function getContent() {
	if (isset ( $_GET ['q'] )) {
		switch ($_GET ['q']) {
			// get Vokabel
			// --------------------------------
			case 'voc' :
				if (isset ( $_GET ['l'] )) {
					if (getVocabulary ( $_GET ['l'] )) {
						// Vokabeln wurden erfolgreich eingelesen
						// TODO voc html
						echo "voc";
					} else {
						// Lektion existiert nicht!
						// TODO html
						echo "lektion-";
					}
				} else {
					// Keine Lektion ausgewählt!
					// TODO html
					echo "lektion--";
				}
				break;
			// get Statistik
			// --------------------------------
			case 'stat' :
				echo '<div id="stastik">Einstellungen</div>';
				// TODO
				break;
			// get Setup
			// --------------------------------
			case 'setup' :
				// TODO
				echo '<div id="stastik">Einstellungen</div>';
				break;
			// get Selection
			// --------------------------------
			case 'sel' :
				getLections ();
				echo '<div id="selection">Auswahl der Lektion</div>';
				break;
			// Standard: Intro Text
			// --------------------------------
			default :
				include ('html/welcome.html');
				break;
		}
	} else {
		// Intro Text
		// --------------------------------
		include ('html/welcome.html');
	}
}
?>