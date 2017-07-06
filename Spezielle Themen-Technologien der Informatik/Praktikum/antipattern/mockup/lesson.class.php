<?php
class Lesson {
	// @var string speichert den Namen der Lektion.
	private $lessonName;
	// @var string speichert den Dateinamen der Lektion
	private $lessonFileName;
	
	public function __construct() {
		/*
		* Der Konstruktor holt die nötigen Vokabeln.
		* Wenn die Lektion als Abfrage erstellt wurde, werden abzufragende Vokabel die möglichen Antworten aus der Datei geholt.
		* Wenn die Lektion als Antwort erstellt wurde, werden die richtige/falsche Antwort geholt.
		*/
	}
	
	public function getVocabulary() {
		/*
		* Holt die entsprechenden Vokabeln aus der Datei.
		*/
	}
}