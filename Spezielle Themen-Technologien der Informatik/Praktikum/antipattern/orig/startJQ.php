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
			<h1>Auswahl</h1>
		</div>
		<div data-role="main" class="ui-content">
		<div data-role="controlgroup" data-type="vertical">

		<?php
			// read info where it is coming from
			$from = $_POST["from"];
	
			// get in uploaded lessons
			$file = fopen("lessons.data", "c+");
			$string = fgets($file);
			
			if($string == "")
			{
				echo "<a class=\"ui-btn\">Keine Lektionen vorhanden</a>";
			}
			else
			{
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

				for($i = 0; $i < sizeof($lessons); $i++)
				{
					echo "
						<form action=\"lessonsJQ.php?lesson=".$lessons[$i]."\" method=\"POST\">
							<input type=\"hidden\" name=\"lesson\" value=\"".$lessons[$i]."\">
							<input type=\"hidden\" name=\"mode\" value=\"\" />
							<input type=\"submit\" value=\"Lektion: ".$lessons_name[$i]."\">
						</form>";
				}
			}
		?>

		</div>
		</div>

			<!-- footer -->
			<div data-role="footer"><div data-role="navbar"><ul><li>

				<!-- Option 1 -->
				<statistic>
					<form action="statisticJQ.php">
						<input type="submit" value="Statistik" />
					</form>
				</statistic>

			</li><li>

				<!-- Option 2 -->
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


