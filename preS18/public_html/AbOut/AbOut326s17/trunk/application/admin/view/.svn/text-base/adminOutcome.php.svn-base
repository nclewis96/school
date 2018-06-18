<!-- View for Add/Edit Outcome panes -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3><?php echo $head; ?></h3>
		<br/>
		<fieldset>
			<label>Outcome Abbreviation: <?php if($outcome != -1) echo $outcome;?></label>
			<?php 
				if($outcome == -1)
				{
					echo '<select name="outcomePrefix">';
					foreach($prefixes as $prefix)
					{
						$prefix = $prefix['oPrefix'];
						echo "<option value='$prefix'>$prefix</option>";
					}
					echo '</select>';
					echo '<input type="text" name="outcomeName" size="1" onkeyup="validateOutcome()" onpaste="setTimeout(validateOutcome, 0)"/>';
				}
			?><br />
			<label>Outcome Description:</label><br />
			<textarea rows="2" cols="50" name='outcomeDescription' onkeyup='validateOutcome()' onpaste='setTimeout(validateOutcome,0)'><?php echo $oText;?></textarea><br />
			<label>Program Abbreviation: </label>
			<select name='program'>
				<option value='CS' <?php if($pAbbrev == 'CS') echo 'selected="selected"'; ?>>CS</option>
				<option value='SE' <?php if($pAbbrev == 'SE') echo 'selected="selected"'; ?>>SE</option>
			</select><br />
			<label>Start Semester: </label>
			<select name='start'>
				<?php
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$semesterDesc = $semester['semester'];
						echo "<option value='$semesterId' ";
						if($semesterId == $beginSem)
							echo 'selected="selected"';
						echo">$semesterDesc</option>\xA";
					}
				?>
			</select><br />
			<label>End Semester: </label>
			<select name='end'>
				<option value='null'>---</option>
				<?php
					foreach($semesters as $semester)
					{
						$semesterId = $semester['semesterId'];
						$semesterDesc = $semester['semester'];
						echo "<option value='$semesterId' ";
						if($semesterId == $endSem)
							echo 'selected="selected"';
						echo ">$semesterDesc</option>\xA";
					}
				?>
			</select><br />
			<br/>
			<input type='hidden' name='outcome' value='<?php echo $outcome;?>'/>
			<input type='submit' name='save' value='Save' />
			<?php
				if($outcome != -1)
					echo "<input type='submit' id='delete' name='delete' value='Delete' onclick='deleteOutcome();'/>";
			?>
			<script>
				validateOutcome();
			</script>
		</fieldset>
	</form>
</div>
