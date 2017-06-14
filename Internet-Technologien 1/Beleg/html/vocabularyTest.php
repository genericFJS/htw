<div class="centered">
	<div data-role="fieldcontain" id="selection">
		<fieldset data-role="controlgroup" data-type="horizontal">
			<input type="radio" name="select" id="AtoB" value="AtoB" <?php if(!$this->reverse){ echo 'checked="checked"';} ?> onClick="switchLanguage(this.id)" />
			<label for="AtoB" data-form="ui-btn-up-a">A &rarr; B</label>
			<input type="radio" name="select" id="BtoA" value="BtoA" <?php if($this->reverse){ echo 'checked="checked"';} ?> onClick="switchLanguage(this.id)" />
			<label for="BtoA" data-form="ui-btn-up-a">A &larr; B</label>
		</fieldset>
	</div>
</div>
<form method="post" id="formAjax" action="<?php echo $_SERVER['REQUEST_URI']?>">
	<div>
		<div class="voc vocLeft">
			<div data-form="ui-body-a" class="ui-body ui-body-a ui-corner-all foreign">
				<p id="foreignVocAjax">
					<?php echo $this->lesson->getForeignVocabulary ( $correctVocabulary ) ?>
				</p>
			</div>
		</div>
		<div class="voc vocRight choice">
			<div data-role="fieldcontain">
				<fieldset data-role="controlgroup">
					<?php
					for($i = 0; $i < 5; $i ++) {
						echo '<input type="radio" name="lesson" id="answer', $i, '" value="', $this->lesson->getVocabularyLine ( $i ), '"/>';
						echo '<label id="answerLabel', $i, '" for="answer', $i, '" data-form="ui-btn-up-a">', $this->lesson->getTranslation ( $i ), '</label>';
					}
					echo '<input checked="checked" id="hiddenCorrectAnswer" type="radio" name="lessonCorrectAnswer" value="', $this->lesson->getVocabularyLine ( $correctVocabulary ), '"/>';
					?>					
				</fieldset>
			</div>
		</div>
	</div>
	<div class="centered">
		<button data-icon="check" data-form="ui-btn-up-a" id="okButton" type="submit">Senden</button>
	</div>
</form>