<!-- View for the Overview Outcome Report generation pane -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action='ReportsFormProcessor.php' method='post' enctype='multipart/form-data'>
		<h3>Overview Outcome Report</h3>
		<br/>
		<fieldset>
			<label>Program:</label>
			<select name='program'>
				<option value='both'>CS/SE</option>
				<option value='cac'>CS</option>
				<option value='eac'>SE</option>
			</select>
			<br />
			<label>Single Semester:</label>
			<select name='single' onchange='updateSingleSemester();'>
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
			<label>Start Semester:</label>
			<select name='start' onchange='updateEndSemester();'>
				<option value='null'>---</option>
				<?php
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$sem = $semester['semester'];
						echo "<option value='$semesterId'>$sem</option>\xA";
					}
				?>
			</select>
			<label>End Semester:</label>
			<select name='end'>
				<option value='null'>---</option>
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
			<label>Show Raw Data:</label>
			<select name='raw'>
				<option value='no'>No</option>
				<option value='yes'>Yes</option>
			</select>
			<br/><br/>
			<input type='hidden' name='view' value='overviewOutcome' />
			<div class='center'>
				<input type='submit' name='pdf' value='Generate Report' />
				<input type='submit' name='csv' value='Generate CSV' />
			</div>
		</fieldset>
	</form>
</div>
