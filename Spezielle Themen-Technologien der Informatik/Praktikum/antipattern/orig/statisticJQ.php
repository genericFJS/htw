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
			<h1>Statistik</h1>
		</div>
		<div data-role="main" class="ui-content">

		<!-- main content -->
		<?php
			// read from all .stat files
			
			// get in uploaded lessons
			$file = fopen("lessons.data", "r");	
			$string = fgets($file);

			// read in all lines			
			for($i = 0; !feof($file); $i++)
			{
				// read in the ; seperated words			
				$lessons[$i] = $string;
				$lessons[$i] = str_replace("\n", "", $lessons[$i]);
	
				// get printing name
				$lessons_name[$i] = str_replace(".txt", "", $lessons[$i]);
				$lessons_name[$i] = str_replace("uploads/", "", $lessons_name[$i]);
	
				// get the next line
				$string = fgets($file);
			}
			fclose($file);

			// save number of lessons
			$lessonCount = $i;
		?>


			<div data-role="controlgroup" data-type="vertical">

		
		<?php

			// read the .stat files and print the stats
			for($i = 0; $i < $lessonCount; $i++)
			{
				// don't print statistics if the lesson file was deleted
				if(file_exists($lessons[$i]))
				{
					echo "<a class=\"ui-btn\">";
	
					// get .stat fileName
					$fileName = $lessons_name[$i].".stat";
					
					// open or create file
					$file = fopen($fileName, "c+") or die("<br>Die Datei kann nicht geöffnet werden!");

					// get content
					$string = fgets($file);
	
					if($string == "")
					{
						// write content
						fwrite($file, "0;0");

						echo $lessons_name[$i].": Richtig 0 / 0";
					}
					else
					{
						// seperate string
						$line = explode(';', $string);
						echo $lessons_name[$i].": Richtig ".$line[0]." / ".$line[1];
					}
					fclose($file);

					echo "</a>";
				}
			}
		?>

		</div>

		
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
				<setup>
					<form action="setupJQ.php">
						<input type="hidden" name="from" value="start">
						<input type="submit" value="Setup" />
					</form>
				</setup>

			</li></ul></div></div>


		</div> 
	</body>
</html>

​


