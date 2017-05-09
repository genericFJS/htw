<?php
include_once 'php/Lesson.class.php';

// prüfe, ob Abfrage hin oder her:
$reverse = false;
if (isset ( $_GET ["r"] ))
	$reverse = true;
// brauche keine speziellen Linien, gib nur neue Lektion:
$answerLines = array (
		- 1 
);
// erzeuge neue Lektion
$lesson = new Lesson ( $_GET ["l"], $reverse, $answerLines );

// wähle zufällige Vokabel aus:
$correctVocabulary = mt_rand ( 0, 4 );
// gebe Vokabeldaten als json aus:
header ( 'Content-Type: application/json' );
echo json_encode ( array (
		'foreignVoc' => $lesson->getForeignVocabulary ( $correctVocabulary ),
		'correctNumber' => $lesson->getVocabularyLine ( $correctVocabulary ),
		'answerVoc0' => $lesson->getTranslation ( 0 ),
		'answerNumber0' => $lesson->getVocabularyLine ( 0 ),
		'answerVoc1' => $lesson->getTranslation ( 1 ),
		'answerNumber1' => $lesson->getVocabularyLine ( 1 ),
		'answerVoc2' => $lesson->getTranslation ( 2 ),
		'answerNumber2' => $lesson->getVocabularyLine ( 2 ),
		'answerVoc3' => $lesson->getTranslation ( 3 ),
		'answerNumber3' => $lesson->getVocabularyLine ( 3 ),
		'answerVoc4' => $lesson->getTranslation ( 4 ),
		'answerNumber4' => $lesson->getVocabularyLine ( 4 ) 
) );
?>