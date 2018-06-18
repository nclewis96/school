<!-- View for Add/Edit Course panes -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data" onsubmit="return courseSubmit()">
		<h3><?php echo $head;?></h3>
		<br/>
		<fieldset>
			<label>Course Abbreviation: <?php if($course != -1) echo $course;?></label>
			<?php 
				if($course == -1)
				{
					echo '<select name="cAbbrev">';
					foreach($prefixes as $prefix)
					{
						$prefix = $prefix['cPrefix'];
						echo "<option value='$prefix'>$prefix</option>";
					}
					echo '</select>';
					echo '<label>Course Number:</label>';
					echo '<input type="text" size="1" name="cNumber" onkeyup="validateCourse()" onpaste="setTimeout(validateCourse, 0)"/>';
				}
			?><br/>
			<label>Course Name: </label><input type='text' name='courseName' size="35" value="<?php echo $courseName;?>" onkeyup='validateCourse()' onpaste='setTimeout(validateCourse, 0)'/><br/>
			<div id="program">
			<input type='checkbox' name='cs' <?php if($csFlag) echo 'checked="checked"';?> onchange='updateCheck("cs"); validateCourse();'/><label>CS</label><br/>
			<input type='checkbox' name='se' <?php if($seFlag) echo 'checked="checked"';?> onchange='updateCheck("se"); validateCourse();'/><label>SE</label><br/>
			</div>
			<br/>
			<label>Start Semester: <?php if($course != -1) echo $semester;?></label>
			<?php
				if($course == -1)
				{
					echo '<select name="start">';
					foreach($semesters as $sem)
					{
						$semId = $sem['semesterId'];
						$semName = $sem['semester'];
						echo "<option value='$semId'>$semName</option>";
					}
					echo '</select>';
				}
			?>
			<br/>
			<label>End Semester: </label>
			<select name='end'>
				<option value='null'>---</option>
				<?php
					foreach($semesters as $sem)
					{
						$semId = $sem['semesterId'];
						$semName = $sem['semester'];
						echo "<option value='$semId'>$semName</option>";
					}
				?>
			</select><br/>
			<br/>
			<h3>Outcomes</h3>
			<div id="outcomes">
			<table id="csOutcomes" <?php if(!$csFlag) echo 'style="display: none;"';?>>
			<?php
				foreach($csOutcomes as $cs)
				{	
					$oAbbrev = $cs['oAbbrev'];
					$oText = $cs['oText'];
					
					echo "<tr><td><input type='checkbox' name='$oAbbrev' value='$oAbbrev'";
					if(in_array($oAbbrev, $outcomes))
						echo 'checked="checked"';
					echo " onchange='validateCourse()'/></td><td style='width:60px;'>$oAbbrev - </td><td>$oText</td></tr>\xA";
				}
			?>
			</table>
			<table id="seOutcomes" <?php if(!$seFlag) echo 'style="display: none;"';?>>
			<?php
				foreach($seOutcomes as $se)
				{	
					$oAbbrev = $se['oAbbrev'];
					$oText = $se['oText'];
					
					echo "<tr><td><input type='checkbox' name='$oAbbrev' value='$oAbbrev'";
					if(in_array($oAbbrev, $outcomes))
						echo 'checked="checked"';
					echo " onchange='validateCourse()'/></td><td style='width:60px;'>$oAbbrev - </td><td>$oText</td></tr>\xA";
				}
			?>
			</table>
			</div>
			<br/>
			<input type='hidden' name='courseId' value='<?php echo $course; ?>'/>
			<input type='submit' name='save' value='Save' />
			<input type='submit' name='reset' value='Reset' />
			<?php
				if($course != -1)
					echo "<input type='submit' id='delete' name='delete' value='Delete' onclick='deleteCourse();'/>";
			?>
			<script>
				validateCourse();
			</script>
		</fieldset>
	</form>
</div>
