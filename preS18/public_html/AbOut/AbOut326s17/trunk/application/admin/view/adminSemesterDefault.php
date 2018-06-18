<!-- View for Default Semester pane -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3>Default Semester</h3>
		<br/>
		<fieldset>
			<label>Default Semester: </label>
			<select name='defaultSemester'>
				<?php
					foreach($semesters as $semester)
					{
						$semId = $semester['semesterId'];
						$sem = $semester['semester'];
						
						echo "<option value='$semId'";
						if($semId == $defaultId)
							echo " selected='selected'";
						echo ">$sem</option>\xA";
					}
				?>
			</select><br />
			<input type='submit' name='save' value='Save Default'/>
		</fieldset>
	</form>
</div>
