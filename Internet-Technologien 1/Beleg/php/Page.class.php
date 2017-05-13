<?php
include_once 'Enums.php';
include_once 'Lesson.class.php';
class page {
	/**
	 *
	 * @var PageState ist der Status der Seite
	 */
	private $state = PageState::__default;
	/**
	 *
	 * @var bool ist der zusätliche Status, ob die Abfrage umgekehrt geschehen soll.
	 */
	private $reverse = false;
	/**
	 *
	 * @var string speichert den Titel der Seite.
	 */
	private $title = 'Vokabeltrainer';
	/**
	 *
	 * @var Lesson speichert die aktuelle Lektion.
	 */
	private $lesson;
	const filesPath = 'lessons/';
	const statisticsExtension = '-stat.txt';
	const fileFormatHTML = '<p>Format der Datei: </p><p><code>Titel der Lektion <br> Wort in Sprache 1 &#8614; [Aussprache Wort in Sprache 1] &#8614; Übersetzung in Sprache 2 &#8614; [Aussprache Wort in Sprache 2]<br>... (mindestens 5 Einträge)</code></p>';
	public $debug = "";
	public $errorMessage = "";
	
	/**
	 * Der Konstruktor bearbeitet die GET-Variablen und speichert sie in $pageState.
	 * Bei der Vokabeltest-Seite wird die entsprechende $lesson intialisiert.
	 * Des weiteren wird hier der Titel der Webseite festgelegt.
	 */
	public function __construct() {
		if (isset ( $_GET ['q'] )) {
			switch ($_GET ['q']) {
				case 'select' :
					$this->state = PageState::Selection;
					$this->setTitle ( 'Auswahl' );
					break;
				case 'stats' :
					$this->state = PageState::Statistics;
					$this->setTitle ( 'Statistik' );
					break;
				case 'setup' :
					$this->state = PageState::Setup;
					$this->setTitle ( 'Setup' );
					break;
				case 'lesson' :
					// Lektion ausgewählt?
					if (isset ( $_GET ['l'] )) {
						// Andere Abfragerichtung?
						if (isset ( $_GET ['r'] ))
							$this->reverse = true;
						$answerLines = array (
								- 1 
						);
						// Antwort auf Abfrage?
						if ($_SERVER ['REQUEST_METHOD'] === 'POST') {
							$this->state = PageState::LessonAnswer;
							$answerLines = $this->getPostAnswers ();
						}
						// erstelle neue Lektion
						$this->lesson = new Lesson ( $_GET ['l'], $this->reverse, $answerLines );
						if ($answerLines [0] < 0) {
							// Wenn es keine Antwort ist, prüfe ob Lektion ok ist.
							if ($this->lesson->isValidLesson ()) {
								$this->state = PageState::Lesson;
								$this->setTitle ( 'lesson' );
							} else {
								$this->state = PageState::WrongLesson;
								$this->setTitle ( 'Falsche Auswahl' );
							}
						} else {
							// Wenn es eine Antwort ist, protokolliere die Antwort
							$this->setTitle ( 'lesson' );
							$this->logAnswer ();
						}
					} else {
						$this->state = PageState::NoLesson;
						$this->setTitle ( 'Keine Auswahl' );
					}
					break;
				case 'task' :
					$this->state = PageState::Task;
					$this->setTitle ( 'Aufgabenbeschreibung' );
					break;
			}
		}
	}
	
	/**
	 * Stellt den Titel der Webseite dar.
	 */
	public function printTitle() {
		echo $this->title;
	}
	/**
	 * Setzt den Titel direkt oder über den Namen der Lektion.
	 *
	 * @param string $title ist der Titel oder 'lesson', wenn der Titel über den Namen der Lektion gesetzt werden soll.
	 */
	private function setTitle($title) {
		if (strcmp ( 'lesson', $title ) == 0) {
			// TODO lesson title (ggf. Kürzung des Titels per Javascript)
			$this->title = $this->lesson->getLessonName ();
		} else {
			$this->title = $title;
		}
	}
	
	/**
	 * Stellt den Inhalt des Main-Contents abhängig vom Status der Webseite dar.
	 */
	public function printMainContent() {
		switch ($this->state) {
			case (PageState::Selection) :
				$this->printSelectionPage ();
				break;
			case PageState::Statistics :
				$this->printStatisticsPage ();
				break;
			case PageState::Setup :
				$this->printSetupPage ();
				break;
			case PageState::WrongLesson :
				$this->printWrongLessonPage ();
				break;
			case PageState::NoLesson :
				$this->printNoLessonPage ();
				break;
			case PageState::Lesson :
				$this->printLessonPage ();
				break;
			case PageState::LessonAnswer :
				$this->printAnswerPage ();
				break;
			case PageState::Task :
				$this->printTaskPage ();
				break;
			default :
				$this->printStartPage ();
				break;
		}
	}
	
	/**
	 * Stellt den Inhalt der Startseite dar (start.html).
	 */
	private function printStartPage() {
		readfile ( 'html/start.html' );
	}
	
	/**
	 * Stellt den Inhalt der Auswahlseite dar, indem er alle Dateien im Ordner der Lektionen auflistet, die nicht mit "-stat" enden.
	 */
	private function printSelectionPage() {
		echo '<ul  data-role="listview" data-inset="true">';
		$dir = new DirectoryIterator ( $this::filesPath );
		foreach ( $dir as $fileinfo ) {
			if (! $fileinfo->isDot ()) {
				$fileName = pathinfo ( $fileinfo->getFilename (), PATHINFO_FILENAME );
				$fileFullPath = $fileinfo->getPath () . '/' . $fileinfo;
				$lection = fgets ( fopen ( $fileFullPath, 'r' ) );
				if (strcmp ( "-stat", substr ( $fileName, - 5 ) ) != 0) {
					echo '<li>
						<a  class="ui-btn ui-btn-icon-right ui-icon-carat-r" data-form="ui-btn-up-a" href="?q=lesson&l=', $fileName, '">', $lection, '</a>
						</li>';
				}
			}
		}
		echo '</ul>';
	}
	
	/**
	 * Stellt eine Auswahlseite zum runterladen/löschen von Lektionen dar.
	 * Standardlektionen (die nicht hochgeladen wurden, erkennbar an einem kürzeren Dateinamen) können nicht gelöscht werden.
	 */
	private function printSetupSelectionPage() {
		echo '<div data-form="ui-body" class="ui-body ui-body-a ui-corner-all"><table id="setupSelect"><tbody>';
		$dir = new DirectoryIterator ( 'lessons/' );
		foreach ( $dir as $fileinfo ) {
			if (! $fileinfo->isDot ()) {
				$fileName = pathinfo ( $fileinfo->getFilename (), PATHINFO_FILENAME );
				$fileFullPath = $fileinfo->getPath () . '/' . $fileinfo;
				$lection = fgets ( fopen ( $fileFullPath, 'r' ) );
				if (strcmp ( "-stat", substr ( $fileName, - 5 ) ) != 0) {
					echo '<tr id="', $fileName, '">
						<td>', $lection, '</td>
						<td><a href="', $fileFullPath, '" class="ui-btn ui-corner-all ui-icon-arrow-d ui-btn-icon-notext" download  data-role="button" data-inline="true">Lektion herunterladen</a></td>
						<td>';
					if (strlen ( $fileName ) > 10)
						echo '<a class="ui-btn ui-corner-all ui-icon-delete ui-btn-icon-notext" data-role="button" data-inline="true" onClick="deleteLesson(\'', $fileFullPath, '\', \'', $fileName, '\')">Lektion löschen</a>';
					else
						echo '&nbsp;';
					echo '</td>
					</tr>';
				}
			}
		}
		echo '</tbody></table></div><div id="errorDelete"></div>';
	}
	
	/**
	 * Stellt die Statistikseite dar.
	 * Dazu wird zu jeder Lektion eine entsprechende stats-Datei gesucht. Wenn keine Datei vorhanden ist, wird 0/0 angezeigt.
	 */
	private function printStatisticsPage() {
		echo '<ul data-role="listview" data-inset="true">';
		$statistics = array ();
		$dir = new DirectoryIterator ( 'lessons/' );
		foreach ( $dir as $fileinfo ) {
			if (! $fileinfo->isDot ()) {
				$fileName = pathinfo ( $fileinfo->getFilename (), PATHINFO_FILENAME );
				$lection = fgets ( fopen ( $fileinfo->getPath () . '/' . $fileinfo, 'r' ) );
				if (strcmp ( "-stat", substr ( $fileName, - 5 ) ) != 0) {
					$stats = $this->getStatsFromFile ( $fileinfo->getPath () . '/' . $fileName . $this::statisticsExtension );
					array_push ( $statistics, array (
							$lection,
							$stats 
					) );
				}
			}
		}
		foreach ( $statistics as $stats ) {
			echo '<li class="centered" data-form="ui-body-a">', $stats [0], '<br>Richtig: ' . $stats [1] [0] . ' / ' . $stats [1] [1] . '</li>';
		}
		echo '</ul>';
	}
	
	/**
	 * Stellt die Setupseite dar.
	 * Diese beinhaltet zum einen den Dateiupload als auch (für Aufgabenstellung optional) das runterladen und löschen von Dateien.
	 */
	private function printSetupPage() {
		if ($_SERVER ['REQUEST_METHOD'] === 'POST') {
			$this->processUploadFile ();
		}
		echo '
		<h2>Datei hochladen</h2>
		<form action="', $_SERVER ['REQUEST_URI'], '" method="post" enctype="multipart/form-data">
  	  <input type="file" name="upfile">
			<div class="centered">
				<button data-icon="plus" data-form="ui-btn-up-a" id="okButton" type="submit">Datei hochladen</button>
			</div>
			<div id="errorUp">', $this->errorMessage, '</div>
		</form>
		<h2>Datei runterladen / löschen</h2>
		';
		$this->printSetupSelectionPage ();
	}
	
	/**
	 * Nutzt: https://php.net/manual/de/features.file-upload.php#114004
	 * Fängt alle möglichen Fehlerzustände beim Hochladen der Datei ab.
	 * Wenn ein Fehler auftritt wird die Fehlermeldung in einer Variablen gespeichert und später ausgegeben.
	 *
	 * @throws RuntimeException gibt mit einem Text aus, was schief gelaufen ist.
	 */
	private function processUploadFile() {
		try {
			// Undefined | Multiple Files | $_FILES Corruption Attack?
			if (! isset ( $_FILES ['upfile'] ['error'] ) || is_array ( $_FILES ['upfile'] ['error'] )) {
				throw new RuntimeException ( 'Keine Datei zum Hochladen ausgewählt.' );
			}
			// Check $_FILES['upfile']['error'] value.
			switch ($_FILES ['upfile'] ['error']) {
				case UPLOAD_ERR_OK :
					break;
				case UPLOAD_ERR_NO_FILE :
					throw new RuntimeException ( 'Datei wurde nicht gesendet.' );
				case UPLOAD_ERR_INI_SIZE :
				case UPLOAD_ERR_FORM_SIZE :
					throw new RuntimeException ( 'Datei zu groß.' );
				default :
					throw new RuntimeException ( 'Unbekannter Fehler.' );
			}
			// Check filesize here.
			if ($_FILES ['upfile'] ['size'] > 1000000) {
				throw new RuntimeException ( 'Datei zu groß.' );
			}
			// Check MIME Type.
			/*
			 * nicht lauffähig auf HTW Server
			 * $finfo = new finfo ( FILEINFO_MIME_TYPE );
			 * if (false === array_search ( $finfo->file ( $_FILES ['upfile'] ['tmp_name'] ), array (
			 * 'txt' => 'text/plain'
			 * ), true )) {
			 */
			/*
			 * Ebenfalls nicht auf HTW Server lauffähig
			 * if (strcmp ( mime_content_type ( $_FILES ['upfile'] ['tmp_name']), 'text/plain' ) != 0 ) {
			 */
			if (strcmp ( pathinfo ( basename ( $_FILES ["upfile"] ["name"] ) ) ['extension'], 'txt' ) != 0) {
				throw new RuntimeException ( 'Falsches Dateiformat. Es sind nur txt-Dateien erlaubt.' );
			}
			// Check if file exists.
			$fileName = sprintf ( '%s/%s%s', $this::filesPath, sha1_file ( $_FILES ['upfile'] ['tmp_name'] ), Lesson::fileExtension );
			if (file_exists ( $fileName )) {
				throw new RuntimeException ( 'Datei existiert bereits.' );
			} else {
				// ... or if a Lesson with the same title exists.
				$dir = new DirectoryIterator ( 'lessons/' );
				foreach ( $dir as $fileinfo ) {
					if (! $fileinfo->isDot ()) {
						$lection = fgets ( fopen ( $fileinfo->getPath () . '/' . $fileinfo, 'r' ) );
						if (strcmp ( $lection, fgets ( fopen ( $_FILES ['upfile'] ['tmp_name'], 'r' ) ) ) == 0)
							throw new RuntimeException ( 'Es existiert bereits eine Lektion mit einem gleichen Namen.' );
					}
				}
			}
			// Check file
			$handle = @fopen ( $_FILES ['upfile'] ['tmp_name'], 'r' );
			if ($handle) {
				$lines = 0;
				while ( ($buffer = fgets ( $handle, 4096 )) !== false ) {
					if (strcmp ( $buffer, $this->stripHTMLChars ( $buffer ) ) != 0)
						throw new RuntimeException ( 'Fehler in Zeile ' . ++ $lines . ': Datei enthält unerlaubte Zeichenfolgen.' );
					$bufferArray = str_getcsv ( $buffer, "	" );
					if ($lines == 0 && sizeof ( $bufferArray ) > 1)
						throw new RuntimeException ( 'Fehler in Zeile ' . ++ $lines . ': Datei enthalt Tabs im Titel.' . $this::fileFormatHTML );
					if ($lines != 0 && sizeof ( $bufferArray ) < 4)
						throw new RuntimeException ( 'Fehler in Zeile ' . ++ $lines . ': Datei ist nicht nach dem benötigten Schema formatiert oder enthält Leerzeilen.' . $this::fileFormatHTML );
					foreach ( $bufferArray as $element ) {
						if (strcmp ( trim ( $element ), "" ) == 0) {
							if ($lines == 0)
								throw new RuntimeException ( 'Fehler in Zeile ' . ++ $lines . ': Titel darf nicht leer sein.' . $this::fileFormatHTML );
							else
								throw new RuntimeException ( 'Fehler in Zeile ' . ++ $lines . ': Felder für Vokabeln dürfen nicht leer sein.' );
						}
					}
					$lines ++;
				}
				if ($lines < 6)
					throw new RuntimeException ( 'Datei enthält nicht genung Vokabel-Einträge.' );
				fclose ( $handle );
			} else {
				throw new RuntimeException ( 'Fehler beim öffnen der Datei zum Überprüfen der Dateistruktur.' );
			}
			if (! move_uploaded_file ( $_FILES ['upfile'] ['tmp_name'], $fileName )) {
				throw new RuntimeException ( 'Hochgeladen Datei konnte nicht gespeichert werden.' );
			}
			echo 'Datei erfolgreich hochgeladen.';
		} catch ( RuntimeException $e ) {
			$this->errorMessage = $e->getMessage ();
		}
	}
	
	/**
	 * aus: https://stackoverflow.com/a/7128879
	 *
	 * @param string $des Zeichenkette mit potentiellen HTML-Zeichen.
	 * @return string Zeichenkette ohne HTML-Zeichen.
	 * @author Mez
	 */
	private function stripHTMLChars($des) {
		// Strip HTML Tags
		$clear = strip_tags ( $des );
		// weiteres wird nicht benötigt:
		/*
		 * // Clean up things like &amp;
		 * $clear = html_entity_decode($clear);
		 * // Strip out any url-encoded stuff
		 * $clear = urldecode($clear);
		 * // Replace non-AlNum characters with space
		 * $clear = preg_replace('/[^A-Za-z0-9]/', ' ', $clear);
		 * // Replace Multiple spaces with single space
		 * $clear = preg_replace('/ +/', ' ', $clear);
		 * // Trim the string of leading/trailing space
		 * $clear = trim($clear);
		 */
		return $clear;
	}
	
	/**
	 * Stellt die Seite dar, die anzeigt, dass die Lektion die mit GET übergeben wurde nicht gefunden werden konnte.
	 */
	private function printWrongLessonPage() {
		echo '
		<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all">
			<h1>Fehler</h1>
			<p>Die Lektion konnte nicht gefunden werden.</p>
		</div>';
	}
	
	/**
	 * Stellt die Seite dar, die anzeigt, dass über GET zwar eine Vokabelabfrage angekündigt wurde, aber keine Lektion ausgewählt wurde.
	 */
	private function printNoLessonPage() {
		echo '
		<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all">
			<h1>Fehler</h1>
			<p>Es wurde keine Lektion ausgewählt.</p>
		</div>';
	}
	
	/**
	 * Stellt die Seite der Vokabelabfrage dar (vocabularyTest.php).
	 */
	private function printLessonPage() {
		$correctVocabulary = mt_rand ( 0, 4 );
		include ('html/vocabularyTest.php');
	}
	
	/**
	 * Stellt die Seite einer beantworteten Vokabelabfrage dar (vocabularyAnswer.php).
	 */
	private function printAnswerPage() {
		$correctVocabulary = 0;
		$wrongVocabulary = 1;
		include ('html/vocabularyAnswer.php');
	}
	
	/**
	 * Stellt den Inhalt der Seite dar, auf der die Aufgabenstellung beschrieben ist (task.html).
	 */
	private function printTaskPage() {
		readfile ( 'html/task.html' );
	}
	
	/**
	 * Stellt den Inhalt des Footers dar.
	 * Aktive Navigationselemente werden nicht angezeigt.
	 */
	public function printFooterContent() {
		echo '<ul>';
		if (! $this->isActive ( PageState::Selection ))
			echo '<li class="', $class, '"><a href="?q=select">Auswahl</a></li>';
		if (! $this->isActive ( PageState::Statistics ))
			echo '<li class="', $class, '"><a href="?q=stats">Statistik</a></li>';
		if (! $this->isActive ( PageState::Setup ))
			echo '<li class="', $class, '"><a href="?q=setup">Setup</a></li>';
		echo '</ul>';
	}
	
	/**
	 * Protokolliere die Antwort einer Vokabelabfrage in der entsprechenden Datei.
	 */
	private function logAnswer() {
		$fileName = $this::filesPath . $this->lesson->getLessonFileName () . $this::statisticsExtension;
		// lese Statistik ein
		$stats = $this->getStatsFromFile ( $fileName );
		// aktualisiere Statistik
		$stats [1] ++;
		if ($this->lesson->isCorrectAnswer ())
			$stats [0] ++;
		// versuche Statistik in Datei zu schreiben
		try {
			if (file_exists ( $fileName ) && ! is_writable ( $fileName ) || ! is_writable ( $this::filesPath ))
				throw new RuntimeException ( 'Statistik konnte nicht gespeichert werden. Stelle sicher, dass entsprechende Dateien und Ordner auf dem Webserver mit den nötigen Schreibrechten eingerichtet sind.' );
			file_put_contents ( $fileName, $stats [0] . "\t" . $stats [1] );
		} catch ( RuntimeException $e ) {
			$this->errorMessage = $e->getMessage ();
		}
	}
	
	/**
	 * Gib die die gePOSTeten Antworten aus.
	 *
	 * @return string[] sind die Antworten (bzw. nur die richtige Antwort, wenn keine Antwort ausgewählt wurde).
	 */
	private function getPostAnswers() {
		$returnArray = array (
				$_POST ["lessonCorrectAnswer"] 
		);
		if (isset ( $_POST ["lesson"] ))
			array_push ( $returnArray, $_POST ["lesson"] );
		return $returnArray;
	}
	
	/**
	 *
	 * @param string $fileName ist der Name der Statistikdatei einer Lektion.
	 * @return number[] gibt die Statistik richtige/alle Vokabeln aus.
	 */
	private function getStatsFromFile($fileName) {
		$stats = array (
				0,
				0 
		);
		$handle = @fopen ( $fileName, 'r' );
		if ($handle) {
			$statsLine = fgets ( $handle, 4096 );
			$statsRead = str_getcsv ( $statsLine, "	" );
			if (sizeof ( $statsRead ) >= 2) {
				$stats [0] = intval ( $statsRead [0] );
				$stats [1] = intval ( $statsRead [1] );
			}
			fclose ( $handle );
		}
		return $stats;
	}
	
	/**
	 * Gibt aus, ob der übergeben Status aktiv ist.
	 *
	 * @param $state Status (in der Regel aus dem Enum PageState)
	 * @return boolean Wahr, wenn Status aktiv ist. Sonst falsch.
	 */
	private function isActive($state) {
		return $this->state == $state;
	}
}