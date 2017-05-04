<?php
include_once 'Enums.php';
include_once 'Lesson.class.php';
class page {
	private $state = PageState::__default;
	private $title = 'Vokabeltrainer';
	private $lesson;
	
	/**
	 * Der Konstruktor bearbeitet die GET-Variablen und speichert sie in $pageState.
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
					if (isset ( $_GET ['l'] )) {
						$this->lesson = new Lesson ( $_GET ['l'] );
						if ($this->lesson->isValidLesson ()) {
							$this->state = PageState::Lesson;
							$this->setTitle ( 'lesson' );
						} else {
							$this->state = PageState::WrongLesson;
							$this->setTitle ( 'Falsche Auswahl' );
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
				echo '<li><a class="ui-btn-a ui-btn ui-btn-icon-right ui-icon-carat-r" data-form="ui-btn-up-a" href="?q=lesson&l=', $lection, '">', $lection, '</a></li>';
			}
		}
		echo '</ul>';
	}
	private function printStatisticsPage() {
		// TODO Statistikseite
		echo 'Hier kommt eine Statistikseite hin.';
	}
	private function printSetupPage() {
		// TODO datei überprüfen, u.a. keine leerzeilen.
		echo 'Hier kommt eine Setupseite hin.';
	}
	private function printWrongLessonPage() {
		echo '<h1>Fehler</h1>', '<p>Die Lektion konnte nicht gefunden werden.</p>';
	}
	private function printNoLessonPage() {
		echo '<h1>Fehler</h1>', '<p>Es wurde keine Lektion ausgewählt.</p>';
	}
	private function printLessonPage() {
		$correctVocabulary = mt_rand ( 0, 4 );
		echo '
		<div class="centered">
			<div data-role="fieldcontain" id="selection"> 
				<fieldset data-role="controlgroup" data-type="horizontal">
					<input type="radio" name="select" id="AtoB" value="list" checked="checked"/> 
					<label for="AtoB" data-form="ui-btn-up-a">A > B</label> 
					<input type="radio" name="select" id="BtoA" value="grid"  /> 
					<label for="BtoA" data-form="ui-btn-up-a">A < B</label> 
				</fieldset> 
			</div>
		</div>
		<form method="post" action=',$_SERVER['REQUEST_URI'],'>
		<div>
			<div class="voc vocLeft">
				<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all foreign">
					<p>' . $this->lesson->getForeignVocabulary ( $correctVocabulary ) . '<br>' . $this->lesson->getIPA ( $correctVocabulary ) . '</p>
				</div>
			</div>
			<div class="voc vocRight choice">
				<div data-role="fieldcontain">
					<fieldset data-role="controlgroup">';
		for($i = 0; $i < 5; $i ++) {
			echo '<input type="radio" name="radio-choice-a" id="'.$this->lesson->getVocabularyLine ( $i ).'" value="' . $this->lesson->getVocabularyLine ( $i ) . '	' . $this->lesson->getVocabularyLine ( $correctVocabulary ) . '"/>';
			echo '<label for="'.$this->lesson->getVocabularyLine ( $i ).'" data-form="ui-btn-up-a">' . $this->lesson->getTranslation ( $i ) . '</label>';
		}
		echo '
					</fieldset>
				</div>
			</div>
		</div>
		<div class="centered">
			<button data-icon="check" data-form="ui-btn-up-a" id="okButton" type="submit">Senden</button>
		</div>
		</form>
';
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