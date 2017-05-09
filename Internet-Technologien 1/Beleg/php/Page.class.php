<?php
include_once 'Enums.php';
include_once 'Lesson.class.php';
class page {
	private $state = PageState::__default;
	private $reverse = false;
	private $title = 'Vokabeltrainer';
	private $lesson;
	const filesPath = 'lessons/';
	const statisticsExtension = '-stat.txt';
	public $debug = "";
	
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
	private function setTitle($title) {
		if (strcmp ( 'lesson', $title ) == 0) {
			// TODO lesson title (ggf. Kürzung des Titels per Javascript)
			$this->title = $this->lesson->getLessonName ();
		} else {
			$this->title = $title;
		}
	}
	
	/**
	 * Stellt den Inhalt des Main-Contents der Webseite dar.
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
	private function printSelectionPage() {
		echo '<ul  data-role="listview" data-inset="true">';
		$dir = new DirectoryIterator ( 'lessons/' );
		foreach ( $dir as $fileinfo ) {
			if (! $fileinfo->isDot ()) {
				$lection = pathinfo ( $fileinfo->getFilename (), PATHINFO_FILENAME );
				if (strcmp ( "-stat", substr ( $lection, - 5 ) ) != 0)
					echo '<li><a  data-ajax="false" class="ui-btn-a ui-btn ui-btn-icon-right ui-icon-carat-r" data-form="ui-btn-up-a" href="?q=lesson&l=', $lection, '">', $lection, '</a></li>';
			}
		}
		echo '</ul>';
	}
	private function printStatisticsPage() {
		echo '<ul data-role="listview" data-inset="true">';
		$statistics = array ();
		$dir = new DirectoryIterator ( 'lessons/' );
		foreach ( $dir as $fileinfo ) {
			if (! $fileinfo->isDot ()) {
				$lection = pathinfo ( $fileinfo->getFilename (), PATHINFO_FILENAME );
				if (strcmp ( "-stat", substr ( $lection, - 5 ) ) != 0) {
					$stats = $this->getStatsFromFile ( $fileinfo->getPath () . '\\' . $lection . $this::statisticsExtension );
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
	private function printSetupPage() {
		if ($_SERVER ['REQUEST_METHOD'] === 'POST') {
			$this->processUploadFile ();
		}
		
		echo '
		<form data-ajax="false" action="', $_SERVER ['REQUEST_URI'], '" method="post" enctype="multipart/form-data">
  	  <input type="file" name="upfile">
			<div class="centered">
				<button data-icon="plus" data-form="ui-btn-up-a" id="okButton" type="submit">Datei hochladen</button>
			</div>
		</form>
		';
	}
	
	/**
	 * Nutzt: https://php.net/manual/de/features.file-upload.php#114004
	 *
	 * @throws RuntimeException
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
			if (file_exists ( $this::filesPath . basename ( $_FILES ["upfile"] ["name"] ) )) {
				throw new RuntimeException ( 'Datei existiert bereits.' );
			}
			// Check file
			$handle = @fopen ( $_FILES ['upfile'] ['tmp_name'], 'r' );
			if ($handle) {
				while ( ($buffer = fgets ( $handle, 4096 )) !== false ) {
					if (strcmp ( $buffer, $this->stripHTMLChars ( $buffer ) ) != 0)
						throw new RuntimeException ( 'Datei enthält unerlaubte Zeichenfolgen.' );
					if (sizeof ( str_getcsv ( $buffer, "	" ) ) < 4)
						throw new RuntimeException ( 'Datei ist nicht nach dem benötigten Schema formatiert oder enthält Leerzeilen.' );
				}
				fclose ( $handle );
			} else {
				throw new RuntimeException ( 'Fehler beim öffnen der Datei zum Überprüfen der Dateistruktur.' );
			}
			// Save file.
			// iconv("utf-8", "cp936", $filename)
			if (! move_uploaded_file ( $_FILES ['upfile'] ['tmp_name'], $this::filesPath . basename ( $_FILES ["upfile"] ["name"] ) )) {
				throw new RuntimeException ( 'Hochgeladen Datei konnte nicht gespeichert werden.' );
			}
			echo 'Datei erfolgreich hochgeladen.';
		} catch ( RuntimeException $e ) {
			echo $e->getMessage ();
		}
	}
	
	/**
	 * aus: https://stackoverflow.com/a/7128879
	 *
	 * @param string $des
	 *        	Zeichenkette mit potentiellen HTML-Zeichen
	 * @return string Zeichenkette ohne HTML-Zeichen
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
	private function printWrongLessonPage() {
		echo '
		<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all">
			<h1>Fehler</h1>
			<p>Die Lektion konnte nicht gefunden werden.</p>
		</div>';
	}
	private function printNoLessonPage() {
		echo '
		<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all">
			<h1>Fehler</h1>
			<p>Es wurde keine Lektion ausgewählt.</p>
		</div>';
	}
	private function printLessonPage() {
		$correctVocabulary = mt_rand ( 0, 4 );
		include ('html/vocabularyTest.php');
	}
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
	private function logAnswer() {
		$fileName = $this::filesPath . $this->lesson->getLessonName () . $this::statisticsExtension;
		// lese Statistik ein
		$stats = $this->getStatsFromFile ( $fileName );
		// aktualisiere Statistik
		$stats [1] ++;
		if ($this->lesson->isCorrectAnswer ())
			$stats [0] ++;
		// schreibe Statistik in Datei
		file_put_contents ( $fileName, $stats [0] . "\t" . $stats [1] );
	}
	private function getPostAnswers() {
		$returnArray = array (
				$_POST ["lessonCorrectAnswer"] 
		);
		if (isset ( $_POST ["lesson"] ))
			array_push ( $returnArray, $_POST ["lesson"] );
		return $returnArray;
	}
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
	 * @param $state Status
	 *        	(in der Regel aus dem Enum PageState)
	 * @return boolean Wahr, wenn Status aktiv ist. Sonst falsch.
	 */
	private function isActive($state) {
		return $this->state == $state;
	}
}