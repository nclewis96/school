<!-- View for the Faculty navigation tree pane -->

<div id="tree" class="equal col2 treeClass">
	<table id="tableNav">
		<?php
			foreach($semesters as $semester)
			{
				$sem = $semester['semester'];
				
				echo "<tr class='d0 expand level0'><td class='treeElement'><span class='toggle collapse'></span>$sem</td></tr>\xA";
				
				$courses = $model->getCoursesForSemester($userId, $sem);
				
				foreach($courses as $course)
				{
					$offeringId = $course['offeringId'];
					$cAbbrev = $course['cAbbrev'];
					$sectionNo = $course['sectionNo'];
					$courseName = $cAbbrev.' '.$course['cName'].', '.$sectionNo;
					
					echo "<tr class='d1 expand level1' style='display: none'><td class='treeElement'><span class='toggle expand'></span><a href='FacultyREST.php?view=offering&amp;offering=$offeringId'>$courseName</a></td></tr>\xA";
					
					$assessments = $model->getAssessmentsForCourse($cAbbrev, $sectionNo, $sem);
					
					echo "<tr class='d2 expand level2' style='display: none;'><td class='treeElement'><a href='FacultyREST.php?view=assessment&amp;assessment=-1&amp;offering=$offeringId'><div id = treeElementDiv>Add Assessment</div></a></td></tr>\xA";
					foreach($assessments as $assessment)
					{
						$assessId = $assessment['assessId'];
						$desc = $assessment['description'];
						
						echo "<tr class='d2 expand level2' style='display: none;'><td class='treeElement'><a href='FacultyREST.php?view=assessment&amp;assessment=$assessId'>$desc</a></td></tr>\xA";
					}
				}
				
				$first = false;
			}
		?>
	</table>
	<?php
		if(isset($_SESSION['facultyTree']))
		{
			$tree = $_SESSION['facultyTree'];
			echo "<script>\$(window).load(function() {expandTree('$tree');});</script>";
		}
	?>
</div>