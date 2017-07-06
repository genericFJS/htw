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
			<h1>Setup</h1>
		</div>
		<div data-role="main" class="ui-content">

		<!-- main content -->
		<?php
			// read info where it is coming from
			$from = $_POST["from"];
		
			// get uploaded file name
			$target_dir = "";//uploads/";
			$target_file = $target_dir . basename($_FILES["fileToUpload"]	["name"]);

			$uploadOk = 1;

			// if there are html tag close stuff in the name replace the name with err			
			if (preg_match('/[\'^£$%&*()}{@#~?><>,|=_+¬-]/', $target_file))
			{
				// one or more of the 'special characters' found in $string
				$target_file = "err";
				echo "<br>Im Dateinamen befinden sich unzulässige Zeichen.";
				$uploadOk = 0;
			}
			

			
			$fileType = pathinfo($target_file,PATHINFO_EXTENSION);

			if(strcmp($from, "setup") == 0)
			{
			
				// Check if the file already exists
				if (file_exists($target_file)) {
					echo "<br>Die Datei existiert bereits.";
					$uploadOk = 0;
				}
		
				//  check if the ending of the file is txt
				if($fileType != "txt") {
					echo "<br>Die Dateiendung muss txt sein.";
					$uploadOk = 0;
				}

				// Check if $uploadOk is set to 0 by an error
				if ($uploadOk == 0) {
					echo "<br>Datei wurde nicht hochgeladen.";

				// if everything is ok, try to upload file
				} 
				else 
				{

					// move the uploaded file to the servers filesystem
					if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file))
					{
						echo "<br>Die Datei ". basename( $_FILES["fileToUpload"]["name"]). " wurde hochgeladen.";

						// write the new path in the lessons.info
						$file = fopen("lessons.data", "a") or die("<br>Die Lessons-Datei kann nicht geöffnet werden!");		
						fwrite($file, $target_file."\n");
						fclose($file);

					} 
					else 
					{
						echo "<br>Es gab einen Fehler beim speichern der hochgeladenen Datei.";
					}
				}
			}
		?>		

		</div>

		<form action="setupJQ.php" method="post" data-ajax="false" enctype="multipart/form-data">
			Datei zum Hochladen wählen:
			<input type="file" name="fileToUpload" id="fileToUpload">
			<input type="hidden" name="from" value="setup">
			<input type="submit" value="Datei hochladen" name="submit">
		</form>

			<!-- footer -->
			<div data-role="footer"><div data-role="navbar"><ul><li>

				<start>
					<form action="startJQ.php" method="POST">
						<input type="submit" value="Auswahl" />
					</form>
				</start>

			</li><li>

				<statistic>
					<form action="statisticJQ.php">
						<input type="submit" value="Statistik" />
					</form>
				</statistic>

			</li></ul></div></div>


		</div> 
	</body>
</html>

​


