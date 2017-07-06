<!DOCTYPE html>
<html>
	<head>
		<meta charset = "UTF-8"/>

		<!-- jQuery stuff -->
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css">
		<script src="https://code.jquery.com/jquery-1.11.3.min.js"></script>
		<script src="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
		<style>
			//[data-role=page]{height: 100% !important; position:relative !important;}
			[data-role=footer]{bottom:0; position:absolute !important; top: auto !important; width:100%;}
		</style>
	</head>

	<body>	

		<div data-role="page">
		<div data-role="header">
			<h1>Lesson</h1>
		</div>
		<div data-role="main" class="ui-content">

		<!-- main content -->

		<!-- javascript -->
		<script>
		var mode = 1;

		// function for the ajax call
		function showHint(str, lesson) 
		{
			num = 0;

			var xmlhttp = new XMLHttpRequest();
			xmlhttp.onreadystatechange = function()
			{
				if (this.readyState == 4 && this.status == 200)
				{
					var myObj = JSON.parse(this.responseText);

					var ok = myObj[10];

					// was there an error getting the words?
					if(ok == 0)
					{
						// error field
						document.getElementById("err").innerHTML = "";		

						// start the form
						document.getElementById("q").innerHTML = myObj[0];

						// radio
						document.getElementById("lab1").innerHTML = myObj[1];
						document.getElementById("poss1").value = myObj[1];
	
						document.getElementById("lab2").innerHTML = myObj[2];
						document.getElementById("poss2").value = myObj[2];
	
						document.getElementById("lab3").innerHTML = myObj[3];
						document.getElementById("poss3").value = myObj[3];
	
						document.getElementById("lab4").innerHTML = myObj[4];
						document.getElementById("poss4").value = myObj[4];
	
						document.getElementById("lab5").innerHTML = myObj[5];
						document.getElementById("poss5").value = myObj[5];
	
						// end
						document.getElementById("e1").value = myObj[6];
						document.getElementById("e2").value = myObj[7];
						document.getElementById("e3").value = myObj[8];
	
						// mode for POST
						document.getElementById("postMode").value = myObj[9];
					}
					else if(ok == 1)
					{
						document.getElementById("send").type = "hidden";

						// error field
						document.getElementById("err").innerHTML = "<br>In der Lektionsdatei befinden sich Zeichen die nicht zulässig sind!<br>";	

						// radio
						document.getElementById("lab1").innerHTML = "error";
						document.getElementById("poss1").value = myObj[1];
						document.getElementById("poss1").type = "hidden";
	
						document.getElementById("lab2").innerHTML = "error";
						document.getElementById("poss2").value = myObj[2];
						document.getElementById("poss2").type = "hidden";
	
						document.getElementById("lab3").innerHTML = "error";
						document.getElementById("poss3").value = myObj[3];
						document.getElementById("poss3").type = "hidden";
	
						document.getElementById("lab4").innerHTML = "error";
						document.getElementById("poss4").value = myObj[4];
						document.getElementById("poss4").type = "hidden";
	
						document.getElementById("lab5").innerHTML = "error";
						document.getElementById("poss5").value = myObj[5];	
						document.getElementById("poss5").type = "hidden";						

					}
					else
					{
						document.getElementById("send").type = "hidden";

						// error field
						document.getElementById("err").innerHTML = "<br>Die Datei kann nicht geöffnet werden!<br>";	

						// radio
						document.getElementById("lab1").innerHTML = "error";
						document.getElementById("poss1").value = myObj[1];
						document.getElementById("poss1").type = "hidden";
	
						document.getElementById("lab2").innerHTML = "error";
						document.getElementById("poss2").value = myObj[2];
						document.getElementById("poss2").type = "hidden";
	
						document.getElementById("lab3").innerHTML = "error";
						document.getElementById("poss3").value = myObj[3];
						document.getElementById("poss3").type = "hidden";
	
						document.getElementById("lab4").innerHTML = "error";
						document.getElementById("poss4").value = myObj[4];
						document.getElementById("poss4").type = "hidden";
	
						document.getElementById("lab5").innerHTML = "error";
						document.getElementById("poss5").value = myObj[5];	
						document.getElementById("poss5").type = "hidden";
					}
				}
			};
		
			xmlhttp.open("GET", "switchLesson.php?m=" + str + "&lesson=" + lesson, true);
			xmlhttp.send();
		}
		</script>


	<?php
		// get post variables

		$lesson = $_POST["lesson"];
		$mode = $_POST["mode"];

		// if no mode was given so far, set mode to 1
		if($mode == "")
		{
			$mode = 1;
		}

		// get .stat fileName
		$lessons_name = str_replace(".txt", "", $lesson);
		$lessons_name = str_replace("uploads/", "", $lessons_name);


		// get the php vars 'lesson' and 'mode' into js vars cause js can't read in POST's
		echo "<script>";
		echo "var lesson = " . json_encode($lesson) . ";";
		echo "mode = " . json_encode($mode) . ";";
		echo "showHint(mode, lesson);";
		echo "</script>";
	?>	
	

	<!-- Error message -->
	<p id="err" style="display:inline"></p>
	

	<!-- switch words buttons -->
	<div data-role="controlgroup" data-type="horizontal">
		<a href="#" class="ui-btn ui-btn-up-c" onclick="showHint(1, lesson)">
			<?php echo "Deutsch -> ".$lessons_name; ?>
		</a>
		<a href="#" class="ui-btn" onclick="showHint(0, lesson)">
			<?php echo $lessons_name." -> Deutsch"; ?>
		</a>
	</div>

	<!-- start Radio with question -->
	<form method="POST" action="resultJQ.php?lesson=<?php echo $lesson;?>"">
		<fieldset data-role="controlgroup">
			<legend>
				Was ist die korrekte Übersetzung für <p id="q" style="display:inline"></p>?
			</legend>

	<!-- radio options -->
	<label for="poss1" id="lab1"></label>
	<input type="radio" name="answer" id="poss1" value="">

	<label for="poss2" id="lab2"></label>
	<input type="radio" name="answer" id="poss2" value="">

	<label for="poss3" id="lab3"></label>
	<input type="radio" name="answer" id="poss3" value="">

	<label for="poss4" id="lab4"></label>
	<input type="radio" name="answer" id="poss4" value="">

	<label for="poss5" id="lab5"></label>
	<input type="radio" name="answer" id="poss5" value="">

	</fieldset>
	<input type="hidden" name="solution" id="e1" value="">
	<input type="hidden" name="translation" id="e2" value="">
	<input type="hidden" name="lesson" id="e3" value="" />
	<input type="hidden" name="mode" id="postMode" value=""/>

	<input type="submit" data-inline="true" id="send" value="Senden">
	</form>
		</div>

			<!-- footer -->
			<div data-role="footer"><div data-role="navbar"><ul><li>

				<!-- Option 1 -->
				<start>
					<form action="startJQ.php">
						<input type="submit" value="Auswahl" />
					</form>
				</start>

			</li><li>

				<!-- Option 2 -->
				<statistic>
					<form action="statisticJQ.php">
						<input type="submit" value="Statistik" />
					</form>
				</statistic>

			</li><li>

				<!-- Option 3 -->
				<setup>
					<form action="setupJQ.php">
						<input type="submit" value="Setup" />
					</form>
				</setup>

			</li></ul></div></div>


		</div> 
	</body>
</html>

​


