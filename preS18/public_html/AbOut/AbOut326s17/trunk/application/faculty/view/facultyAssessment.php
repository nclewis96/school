<!-- View for Add/Edit Assessment panes -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="FacultyFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3><?php echo $head; ?></h3>
		<br/>
		<fieldset>
			<label><?php echo "$courseAbbrev $courseName, $semester, $sectionNo"; ?></label><br />
			<label>Instructor: <?php echo $name; ?></label><br />
			<label>Assessment Description: </label>
			<input type="text" name="asDesc" id="asDesc" size="50" value="<?php echo $desc; ?>" onkeyup='validateAssessment()' onpaste='setTimeout(validateAssessment, 0)'/><br />
			<label>Maximum Points: </label>
			<input type="text" name="maxText" id="maxText" size="1" value="<?php echo $maxPoints; ?>" onkeyup='validateAssessment()' onpaste='setTimeout(validateAssessment, 0)'/><br />
			<br/>
			<h3>Outcomes</h3>
			<div id="outcomes">
			<?php
				foreach($outcomes as $outcome)
				{
					$oAbbrev = $outcome['oAbbrev'];
					$oText = $outcome['oText'];
					
					echo "<input type='checkbox' name='$oAbbrev' value='$oAbbrev' "; 
					//find out if this assessment uses this outcome
					foreach($assessmentOutcomes as $o)
					{
						if($o[0] == $oAbbrev)
						{
							echo "checked='checked'"; 
							break;
						}
					}
					echo "onchange='validateAssessment()'/>$oAbbrev - $oText<br />\xA";
				}
			?>
			</div>
			<br/>
			<h3 style ="text-align: left;">Scores</h3>
			<table id="stdntTable">
				<tr><th style="padding: 0px 50px">Students</th><th>Points</th><th style="padding: 0px 30px">Percentage</th></tr>
				<?php
					$index = 1;
					foreach($students as $student)
					{
						$name = $student['sName'];
						$id = $student['studentId'];
						$score = $model->getStudentScoreForAssessment($assessId, $id);
						
						if($score == null)
							$score = 0;
						
						echo "<tr><td>$index. $name</td>";
						echo "<td><input type='text' name='student$id' value='$score' size='2' onkeyup='validateAssessment()' onpaste='setTimeout(validateAssessment, 0)'/></td>";
						$percent = 0;
						if($maxPoints != 0)
						{
							$percent = round(100 * $score / $maxPoints, 2);
						}
						echo "<td align='center'>$percent%</td></tr>\xA";
						$index++;
					}
				?>
			</table><br/>
			<input type="hidden" name="assessId" value="<?php echo $assessId; ?>" />
			<input type="hidden" name="offeringId" value="<?php echo $offeringId; ?>" />
			<input type="submit" name="save" id="save" value="Save" />
			<input type="submit" name="reset" id="reset" value="Reset" />
			<script>
				validateAssessment();
			</script>
			<?php
				if($assessId > -1)
					echo "<input type='submit' id='delete' name='delete' value='Delete' onclick='deleteAssessment();'/>";
			?>
		</fieldset>
	</form>
</div>
