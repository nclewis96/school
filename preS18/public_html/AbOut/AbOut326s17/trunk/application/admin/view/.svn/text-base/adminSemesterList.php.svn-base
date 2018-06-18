<!-- View for Semester List pane -->

<div id="form" class='equal col1 dispForms'>
	<form id='dataForm' action="AdminFormProcessor.php" method="post" enctype="multipart/form-data">
		<h3>Semester List</h3>
		<br/>
		<ul>
			<?php
				for($i = count($semesters) - 1; $i >= 0; $i--)
				{
					$sem = $semesters[$i]['semester'];
					echo "<li>$sem ";
					if($semesters[$i]['semesterId'] == $defaultId)
						echo '<span style="font-style: italic;">(default semester)</span>';
					echo '</li>';
				}
			?>
		</ul>
	</form>
</div>
