<!-- View for the CORE Report generation pane -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action='ReportsFormProcessor.php' method='post' enctype='multipart/form-data'>
		<h3>C.O.R.E. Report</h3>
		<br/>
		<fieldset>
			<label>Course:</label>
			<select name='course' onchange='updateSectionNo();'>
				<?php
					foreach($courses as $course)
					{
						$courseName = $course['cName'];
						$courseAbbrev = $course['cAbbrev'];
						echo "<option value='$courseAbbrev'>$courseAbbrev - $courseName</option>\xA";
					}
				?>
			</select>
			<br />
			<label>Semester:</label>
			<select name='semester' onchange='updateSectionNo();'>
				<?php
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$sem = $semester['semester'];
						echo "<option value='$semesterId'>$sem</option>\xA";
					}
				?>
			</select>
			<br />
			<label>Section Number:</label>
			<select name='section'>
				<!-- javascript will populate based on selected course -->
			</select>
			<script>
				updateSectionNo();
			</script>
			<br />
			<label>Show Raw Data:</label>
			<select name='raw'>
				<option value='no'>No</option>
				<option value='yes'>Yes</option>
			</select>
			<br/><br/>
			<input type='hidden' name='view' value='core' />
			<div class='center'>
				<input type='submit' name='pdf' value='Generate Report' />
				<input type='submit' name='csv' value='Generate CSV' />
			</div>
		</fieldset>
	</form>
</div>
