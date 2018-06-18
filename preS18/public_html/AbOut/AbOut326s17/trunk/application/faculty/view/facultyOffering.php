<!-- View for Edit Offering pane -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="FacultyFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3><?php echo $head; ?></h3>
		<br/>
		<fieldset>
			<label><?php echo "$semester, Section $sectionNo, $name"; ?></label><br />
			<input type="submit" name="addAssessment" value="Add Assessment" />
			<input type="submit" name="report" value="Generate CORE Report" />
			<br /><br />
			<h3>Outcomes</h3>
			<div id="outcomes">
			<table id="outcomeTable">
				<?php
					foreach($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						$oText = $outcome['oText'];
						$percent = $model->calcPercent($oAbbrev, $courseAbbrev, $sectionNo, $semesterId);
						$out = sprintf(" - %.0f%%", round($percent));
						echo "<tr><td style='width: 50px; padding: 1px 0px;'>$oAbbrev</td><td style='width: 40px;'>$out</td><td>$oText</td></tr>\xA";
					}
				?>
			</table>
			</div>
			<br />
			<div class="students">
				<h3 style="text-align: left;">Students</h3>
				<table id='stdntTable'>
					<?php
						$index = 1;
						foreach($students as $student)
						{
							$sName = $student['sName'];
							$studentId = $student['studentId'];
						
							echo "<tr><td>$index. $sName </td><td style='padding: 0px 30px'><input type='submit' name='remove[$studentId]' value='Remove' /></td></tr>\xA";
							$index++;
						}
					?>
				</table>
				<div>
					<input type='text' name='addStudent' onkeyup='validateName(this)' onpaste='var e=this; setTimeout(function(){validateName(e);}, 0);'/>
					<input type='submit' name='add' value='Add' disabled='disabled'/>
					<br />
					<input type='submit' name='export' value='Export Students To File'/>
					<script>
						if($('#stdntTable tr').length <= 0)
							$('input[name="export"]').attr('disabled', 'disabled');
					</script>
					<br />
				</div>
			</div>
			<input type='hidden' name='offeringId' value='<?php echo $offeringId; ?>' />
		</fieldset>
	</form>
</div>
