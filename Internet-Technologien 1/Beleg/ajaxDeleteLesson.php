<?php
if (unlink ( $_GET ["f"] ))
	echo "true";
else 
	echo "false";
?>