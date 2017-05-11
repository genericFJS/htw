<div id="errorChange"> <?php echo $this->errorMessage; ?></div>
<div data-form="ui-body-a" class="<?php if ($this->lesson->isCorrectAnswer()) echo 'rightAnswer'; else echo 'wrongAnswer';?> ui-body ui-body-a ui-corner-all">
	<p><?php echo $this->lesson->getForeignVocabulary ( $correctVocabulary ); ?></p>
	<p><?php echo $this->lesson->getForeignIPA ( $correctVocabulary ); ?></p>
	<?php if (!$this->lesson->isCorrectAnswer()): if(!$this->lesson->isAnswerGiven()): ?>
	<p class="wrongTranslation"><?php echo $this->lesson->getTranslation ( $wrongVocabulary ); ?></p>
	<?php else: ?>
	<p class="wrongTranslation">keine Auswahl</p>	
	<?php  endif; endif;?>
	<p><?php echo $this->lesson->getTranslation($correctVocabulary); ?></p>
</div>
<div class="centered">
	<a id="okButton" class="ui-btn ui-icon-forward ui-btn-icon-left" href="<?php echo $_SERVER['REQUEST_URI']?>">Weiter</a>
</div>