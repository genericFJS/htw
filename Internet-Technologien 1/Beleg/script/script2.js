$(document).on('click', 'a', function(e) {
	e.preventDefault();
	changePageContent(this.href);
});

function changePageContent(fullPath) {
	window.history.pushState({}, "", fullPath);
	var path = fullPath.split('?')[1];
	$('main').load("ajaxPageContent.php?ajaxContent=main&" + path, function() {
		$('main').enhanceWithin();
	});
	$('#footerContent').load("ajaxPageContent.php?ajaxContent=footer&" + path, function() {
		$('footer').enhanceWithin();
	});
}