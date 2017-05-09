<?php
include_once 'Enums.php';
class Lesson {
	private $lessonStatus;
	private $lessonName;
	private $lessonFileName;
	/**
	 * Array, dass die Arrays von den Vokabeln speichert.
	 * Die Vokabel-Arrays haben die Form (Fremdwort, Lautschrift des Fremdwortes, Vokabel, Lautschrift der Vokabel, Zeilennummer).
	 * Wenn das Objekt als Antwort erstellt wurde, ist das 1. Element die richtige Antwort und (falls falsch) das zweite die falsche.
	 *
	 * @var unknown
	 */
	private $vocabulary;
	private $correctAnswer;
	private $answerGiven;
	const filePath = 'lessons/';
	const fileExtension = '.txt';
	
	/**
	 * Der Konstruktor holt die abzufragende Vokabel (inklusive Lautschrift) und die fünf möglichen Antworten aus der übergebenen Datei.
	 *
	 * @param string $lessonName
	 *        	Der Dateiname der Lektion.
	 */
	public function __construct($lessonName, $reverse, $answerLines) {
		$lessonFilePath = Lesson::filePath . $lessonName . Lesson::fileExtension;
		$this->lessonFileName = $lessonName;
		if (file_exists ( $lessonFilePath )) {
			$handle = @fopen ( $lessonFilePath, "r" );
			if ($handle) {
				if ($answerLines [0] < 0) {
					// Berechne die Anzahl der Zeilen in der Datei und wähle 5 zufällige Zeilen aus. Speichere die Zeilennummern in einem Array.
					$totalRows = -1;
					while ( ($buffer = fgets ( $handle, 4096 )) !== false ) {
						$totalRows ++;
					}
					if ($totalRows < 6) {
						$this->lessonStatus = LessonState::NotEnoughFileLines;
						return;
					}
					$randomVocabularyLineNumbers = $this->UniqueRandomNumbersWithinRange ( 0, $totalRows - 1, 5 );
					rewind ( $handle );
					// Speichere die Einträge der zufällig ausgewählten Zeilen in der Vokabelliste.
					$currentVocabularyFileLine = 0;
					$vocabularyFound = 0;
					$this->lessonName = fgets ( $handle, 4096 );
					while ( ($buffer = fgets ( $handle, 4096 )) !== false && $vocabularyFound < 5 ) {
						$entryBuffer = str_getcsv ( $buffer, "	" );
						$entryAdded = - 1;
						switch ($currentVocabularyFileLine) {
							case $randomVocabularyLineNumbers [0] :
								$entryAdded = 0;
								break;
							case $randomVocabularyLineNumbers [1] :
								$entryAdded = 1;
								break;
							case $randomVocabularyLineNumbers [2] :
								$entryAdded = 2;
								break;
							case $randomVocabularyLineNumbers [3] :
								$entryAdded = 3;
								break;
							case $randomVocabularyLineNumbers [4] :
								$entryAdded = 4;
								break;
						}
						if ($entryAdded >= 0) {
							if (! $reverse) {
								$this->vocabulary [$entryAdded] [0] = $entryBuffer [0];
								$this->vocabulary [$entryAdded] [1] = $entryBuffer [1];
								$this->vocabulary [$entryAdded] [2] = $entryBuffer [2];
								$this->vocabulary [$entryAdded] [3] = $entryBuffer [3];
							} else {
								$this->vocabulary [$entryAdded] [0] = $entryBuffer [2];
								$this->vocabulary [$entryAdded] [1] = $entryBuffer [3];
								$this->vocabulary [$entryAdded] [2] = $entryBuffer [0];
								$this->vocabulary [$entryAdded] [3] = $entryBuffer [1];
							}
							$this->vocabulary [$entryAdded] [4] = $randomVocabularyLineNumbers [$entryAdded];
							$vocabularyFound ++;
						}
						$currentVocabularyFileLine ++;
					}
				} else {
					// Wenn Lesson als Antwort generiert wird, lade nur die Antwort-Daten.
					$row = 0;
					$linesToRead = 1;
					$this->answerGiven = (sizeof ( $answerLines ) < 2);
					if ($this->answerGiven) {
						$this->correctAnswer = false;
						$answerLines[1] = -1;
					} else {
						if ($answerLines [0] == $answerLines [1]) {
							$this->correctAnswer = true;
						} else {
							$this->correctAnswer = false;
							$linesToRead = 2;
						}
					}
					$this->lessonName = fgets ( $handle, 4096 );
					while ( ($buffer = fgets ( $handle, 4096 )) !== false && $linesToRead > 0 ) {
						if ($row == $answerLines [0] || $row == $answerLines [1]) {
							$index = 1;
							if ($row == $answerLines [0])
								$index = 0;
							$entryBuffer = str_getcsv ( $buffer, "	" );
							if (! $reverse) {
								$this->vocabulary [$index] [0] = $entryBuffer [0];
								$this->vocabulary [$index] [1] = $entryBuffer [1];
								$this->vocabulary [$index] [2] = $entryBuffer [2];
								$this->vocabulary [$index] [3] = $entryBuffer [3];
							} else {
								$this->vocabulary [$index] [0] = $entryBuffer [2];
								$this->vocabulary [$index] [1] = $entryBuffer [3];
								$this->vocabulary [$index] [2] = $entryBuffer [0];
								$this->vocabulary [$index] [3] = $entryBuffer [1];
							}
							$linesToRead --;
						}
						$row ++;
					}
				}
				$this->lessonStatus = LessonState::Valid;
				fclose ( $handle );
			}
		} else {
			$this->lessonStatus = LessonState::FileNotFound;
		}
	}
	
	/**
	 * https://stackoverflow.com/a/5612704
	 *
	 * @param integer $min        	
	 * @param integer $max        	
	 * @param integer $quantity        	
	 * @return array
	 * @author Anne
	 */
	private function UniqueRandomNumbersWithinRange($min, $max, $quantity) {
		$numbers = range ( $min, $max );
		shuffle ( $numbers );
		return array_slice ( $numbers, 0, $quantity );
	}
	public function isValidLesson() {
		return ($this->lessonStatus == LessonState::Valid);
	}
	public function getLessonStatus() {
		return $this->lessonStatus;
	}
	public function getLessonName() {
		return $this->lessonName;
	}
	public function getLessonFileName(){
		return $this->lessonFileName;
	}
	public function getForeignVocabulary($entryNumber) {
		return $this->vocabulary [$entryNumber] [0];
	}
	public function getForeignIPA($entryNumber) {
		return $this->vocabulary [$entryNumber] [1];
	}
	public function getTranslation($entryNumber) {
		return $this->vocabulary [$entryNumber] [2];
	}
	public function getVocabularyLine($entryNumber) {
		return $this->vocabulary [$entryNumber] [4];
	}
	public function isCorrectAnswer() {
		return $this->correctAnswer;
	}
	public function isAnswerGiven(){
		return $this->answerGiven;
	}
}