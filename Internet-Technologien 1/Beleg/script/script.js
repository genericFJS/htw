/*var minVocSize = 250;
var minNavSize = 100;

// Anpassung der Größe von Objekten je nach Fensterbreite
function resizeDivs() {
	// Ändere Größe der Vokabelfelder abhängig von der Fenstergröße
	if ($(window).width() < (minVocSize * 1.02) * 2) {
		$(".voc", $.mobile.activePage).removeClass("two").addClass("one");
	} else {
		$(".voc", $.mobile.activePage).removeClass("one").addClass("two");
	}
	// Ändere Größe der Navigationsfelder abhängig von der Fenstergröße / Anzahl der Navigationsfelder
	var navElemCount = $(".topnav li", $.mobile.activePage).length;
	if ($(window).width() < (minNavSize * 1.02) * navElemCount) {
		$(".topnav li", $.mobile.activePage).removeClass("two").removeClass("three").addClass("one");
	} else {
		if (navElemCount === 2) {
			$(".topnav li", $.mobile.activePage).removeClass("three").addClass("two");
		} else {
			$(".topnav li", $.mobile.activePage).removeClass("two").addClass("three");
		}
	}
	//$("#debug", $.mobile.activePage).html("test");
}

$(window).on("resize pagebeforeshow", resizeDivs);*/