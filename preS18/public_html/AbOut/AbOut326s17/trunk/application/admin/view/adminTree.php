<!-- View for the Administrator navigation tree pane -->
<div id="tree" class="equal col2 treeClass">
	<table id="tableNav">
		<?php
			echo "<tr class='d0 expand level0'><td class='treeElement'><span class='toggle collapse'></span>Courses</td></tr>\xA";
			
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=course&amp;course=-1' id='treeElementDiv'>Add Course</a></td></tr>\xA";
			foreach($courses as $course)
			{
				$cAbbrev = htmlentities($course['cAbbrev']);
				$courseName = htmlentities($course['cName']);
				
				echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><span class='toggle expand'></span><a href='AdminREST.php?view=course&amp;course=$cAbbrev'>$cAbbrev - $courseName</a></td></tr>\xA";
				
				$offerings = $model->getOfferings($cAbbrev);
				
				echo "<tr class='d2 expand level2' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=offering&amp;offering=-1&amp;course=$cAbbrev' id='treeElementDiv'>Add Offering</a></td></tr>\xA";
				foreach($offerings as $offering)
				{
					$semester = $offering['semester'];
					$sectionNo = $offering['sectionNo'];
					$offeringId = $offering['offeringId'];
					
					echo "<tr class='d2 expand level2' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=offering&amp;offering=$offeringId'>$semester, $sectionNo</a></td></tr>\xA";
				}
			}
			
			echo "<tr class='d0 expand level0'><td class='treeElement'><span class='toggle collapse'></span>Outcomes</td></tr>\xA";
			
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=outcome&amp;outcome=-1' id='treeElementDiv'>Add Outcome</a></td></tr>\xA";
			foreach($outcomes as $outcome)
			{
				$oAbbrev = $outcome['oAbbrev'];
				echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=outcome&amp;outcome=$oAbbrev'>$oAbbrev</a></td></tr>\xA";
			}
			
			echo "<tr class='d0 expand level0'><td class='treeElement'><span class='toggle collapse'></span>Semesters</td></tr>\xA";
			
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=semester&amp;action=add' id='treeElementDiv'>Add Semester</a></td></tr>\xA";
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=semester&amp;action=default' id='treeElementDiv'>Change Default Semester</a></td></tr>\xA";
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=semester&amp;action=list' id='treeElementDiv'>List All Semesters</a></td></tr>\xA";
			
			echo "<tr class='d0 expand level0'><td class='treeElement'><span class='toggle collapse'></span>Users</td></tr>\xA";
			
			echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=user&amp;user=-1' id='treeElementDiv'>Add User</a></td></tr>\xA";
			foreach($users as $user)
			{
				$uName = $user['uName'];
				$userId = $user['userId'];
				echo "<tr class='d1 expand level1' style='display: none;'><td class='treeElement'><a href='AdminREST.php?view=user&amp;user=$userId'>$uName</a></td></tr>\xA";
			}
		?>
	</table>
	<?php
		if(isset($_SESSION['adminTree']))
		{
			$tree = $_SESSION['adminTree'];
			echo "<script>\$(window).load(function() {expandTree('$tree');});</script>";
		}
	?>
</div>