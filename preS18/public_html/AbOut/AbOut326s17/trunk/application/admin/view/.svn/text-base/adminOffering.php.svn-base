<!-- View for Add/Edit Offering panes -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data" onsubmit="return checkOffering() && deleteStudent(this);">
		<h3><?php echo $head;?></h3>
		<br/>
		<fieldset>
			<label>Semester: <?php if($offering > -1) echo $semester;?></label>
			<?php 
				if($offering < 0)
				{
					echo '<select name="single">';
					
					foreach($semesters as $sem)
					{
						$semId = $sem['semesterId'];
						$sem = $sem['semester'];
						echo "<option value='$semId'>$sem</option>";
					}
					
					echo '</select>';
				}
			?>
			<label>Section </label><input type='text' name='section' size="1" value='<?php echo $sectionNo;?>' onkeyup='validateOffering()' onpaste='setTimeout(validateOffering, 0);'/>
			<select name='user'>
				<?php
					foreach($users as $user)
					{
						$id = $user['userId'];
						$uName = $user['uName'];
						
						echo "<option value='$id' ";
						if($id == $userId)
							echo 'selected="selected"';
						echo ">$uName</option>";
					}
				?>
			</select>
			<br/><br/>
			<h3>Outcomes</h3>
			<div id="outcomes">
			<table>
				<?php
					foreach($outcomes as $outcome)
					{
						$oAbbrev = $outcome['oAbbrev'];
						$oText = $outcome['oText'];
						
						if(in_array($oAbbrev, $outcomeAbbrevs))
							echo "<tr><td style='width: 60px; padding:1px 0px;'>$oAbbrev -</td><td>$oText</td></tr>";
					}
				?>
			</table>
			</div>
			<br/>
			<table>
				<tr><th colspan='2'><h3 style='text-align: left;'>Students</h3></th></tr>
				<?php
					$index = 1;
					foreach($students as $student)
					{
						$sName = $student['sName'];
						$studentId = $student['studentId'];
						
						echo "<tr><td>$index. $sName</td><td><input type='submit' name='remove[$studentId]' value='Remove' onclick='removeSet(this);'/></td></tr>";
						$index++;
					}
					
					if(count($students) > 0) 
					{
						echo "<tr><td></td><td><input type='submit' name='removeAll' value='Remove All' onclick='removeSet(this);'/></td></tr>";
					}
				?>
				<tr><td><input type='text' name='student' onkeyup='validateOffering()' onpaste='setTimeout(validateOffering, 0);'/></td><td><input type='submit' name='add' value='Add' disabled='disabled'/></td></tr>
				<tr><td></td><td><input type='button' value='Import Students From File' onclick="$('#importRow').show(); $(this).hide();"/></td></tr>
				<tr id='importRow' style='display: none;'>
					<td><input style="width: 185px;" type='file' name='file'></td>
					<td><input type='submit' name='import' value='Import'/></td>
				</tr>
			</table>
			<br/>
			<input type='hidden' name='offeringId' value='<?php echo $offering;?>'/>
			<input type='hidden' name='course' value='<?php echo $course;?>'/>
			<input type='submit' name='save' value='Save' onclick='addOffering();'/>
			<?php
				if($offering > -1)
				{
					echo "<input type='submit' id='delete' name='delete' value='Delete' onclick='deleteOffering();'/>";
				}
			?>
			<script>
				validateOffering();
			</script>
		</fieldset>
	</form>
</div>
