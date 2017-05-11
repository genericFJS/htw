/**
 * Ändert die Abfragerichtung der Sprache, indem die entsprechenden Felder ausgetauscht werden und die Adresszeile korrigiert wird.
 * 
 * @param id ist die ID der Schaltfläche, die diese Funktion aufruft.
 * @returns true/false wenn es die Sprache geändert hat oder nicht.
 */
function switchLanguage(id) {
	var reverse = '';
	if (getQueryVariable('r') != 'false' && id == 'BtoA')
		return false;
	if (getQueryVariable('r') == 'false' && id == 'AtoB')
		return false;
	if (id == 'BtoA')
		reverse = '&r';
	var link = "?q=" + getQueryVariable('q') + "&l=" + getQueryVariable('l') + reverse;
	// setze Adresszeile neu
	window.history.pushState({}, "", link);
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			var vocInfo = JSON.parse(this.responseText);
			// setze label
			document.getElementById("foreignVocAjax").innerHTML = vocInfo['foreignVoc'];
			document.getElementById("answerLabel0").innerHTML = vocInfo['answerVoc0'];
			document.getElementById("answerLabel1").innerHTML = vocInfo['answerVoc1'];
			document.getElementById("answerLabel2").innerHTML = vocInfo['answerVoc2'];
			document.getElementById("answerLabel3").innerHTML = vocInfo['answerVoc3'];
			document.getElementById("answerLabel4").innerHTML = vocInfo['answerVoc4'];
			// setze values
			document.getElementById("answer0").value = vocInfo['answerNumber0'];
			document.getElementById("answer1").value = vocInfo['answerNumber1'];
			document.getElementById("answer2").value = vocInfo['answerNumber2'];
			document.getElementById("answer3").value = vocInfo['answerNumber3'];
			document.getElementById("answer4").value = vocInfo['answerNumber4'];
			document.getElementById("hiddenCorrectAnswer").value = vocInfo['correctNumber'];
			// setze link
			document.getElementById("formAjax").action = link;
		}
	};
	xmlhttp.open("GET", "ajaxVocabulary.php" + link, true);
	xmlhttp.send();
	return true;
}

/**
 * Löscht eine Lektion bzw. deren Datei
 * 
 * @param path ist der Pfad zu der Datei der Lektion, die gelöscht werden soll.
 * @param id ist die ID der Tabellenzeile, deren Datei gelöscht werden soll.
 * @returns nichts
 */
function deleteLesson(path, id) {
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			if (this.responseText == "true") {
				document.getElementById(id).innerHTML = "<td> Datei wurde gelöscht! </td>";
			} else {
				document.getElementById("errorDelete").innerHTML = "Datei konnte nicht gelöscht werden!";
			}
		}
	};
	xmlhttp.open("GET", "ajaxDeleteLesson.php?f=" + path, true);
	xmlhttp.send();
}

/**
 * von https://css-tricks.com/snippets/javascript/get-url-variables/
 * 
 * @param variable ist die GET Variable, deren Wert benötigt wird.
 * @returns entweder den Wert der GET Variable (ggf. undefined) oder false.
 */
function getQueryVariable(variable) {
	var query = window.location.search.substring(1);
	var vars = query.split("&");
	for (var i = 0; i < vars.length; i++) {
		var pair = vars[i].split("=");
		if (pair[0] == variable) {
			return pair[1];
		}
	}
	return 'false';
}