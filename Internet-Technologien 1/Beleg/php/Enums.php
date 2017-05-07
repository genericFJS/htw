<?php
/**
 * https://stackoverflow.com/a/254543
 * @author Brian Cline
 *
 */
abstract class BasicEnum {
	private static $constCacheArray = NULL;
	private static function getConstants() {
		if (self::$constCacheArray == NULL) {
			self::$constCacheArray = [ ];
		}
		$calledClass = get_called_class ();
		if (! array_key_exists ( $calledClass, self::$constCacheArray )) {
			$reflect = new ReflectionClass ( $calledClass );
			self::$constCacheArray [$calledClass] = $reflect->getConstants ();
		}
		return self::$constCacheArray [$calledClass];
	}
	public static function isValidName($name, $strict = false) {
		$constants = self::getConstants ();
		
		if ($strict) {
			return array_key_exists ( $name, $constants );
		}
		
		$keys = array_map ( 'strtolower', array_keys ( $constants ) );
		return in_array ( strtolower ( $name ), $keys );
	}
	public static function isValidValue($value, $strict = true) {
		$values = array_values ( self::getConstants () );
		return in_array ( $value, $values, $strict );
	}
}

/**
 * Beschreibt die möglichen Zustände der Webseite.
 * @author jonatan
 *
 */
class PageState extends BasicEnum {
	const __default = self::Start;
	const Start = 0;
	const Task = 1;
	const Selection = 10;
	const Statistics = 20;
	const Setup = 30;
	const Lesson = 40;
	const NoLesson = 41;
	const WrongLesson = 42;
	const LessonAnswer = 43;
}

class LessonState extends BasicEnum {
	const __default = self::FileNotFound;
	const FileNotFound = 0;
	const NotEnoughFileLines = 1;
	const OtherError = 10;
	const Valid = 20;
}