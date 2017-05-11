<?php
include_once 'php/Page.class.php';

$page = new Page ();

switch ($_GET ['ajaxContent']) {
	case 'main' :
		echo $page->printMainContent ();
		break;
	default :
		echo $page->printFooterContent ();
		break;
}
?>