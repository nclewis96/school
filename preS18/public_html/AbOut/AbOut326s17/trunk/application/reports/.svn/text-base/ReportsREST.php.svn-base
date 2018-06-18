<?php
/** 
* Reports REST API - provides interface for AJAX
*/

	require_once('../includes/Bootstrap.php');
	include_once(INCLUDE_PATH.'startup.php');
	
	if(!isset($model))
	{
		include('model/ReportsModel.php');
		$model = new ReportsModel($DB_Read, $DB_Write);
	}
	
	if(isset($_GET['request']))
	{
		$request = $_GET['request'];
		
		if($request == 'section')
		{
			$course = $_GET['course'];
			$semester = $_GET['semester'];
			$sectionNo = $model->getClassSectionNumbers($course, $semester);
			foreach($sectionNo as $s)
			{
				echo $s['sectionNo']."\xA";
			}
		}
	}
	else if(isset($_GET['view']))
	{
		$semesters = $model->getSemesters();
	
		$view = $_GET['view'];
	
		if($view == 'overviewOutcome')
		{
			include('view/reportsOverviewOutcome.php');
		}
		else if($view == 'course')
		{
			include('view/reportsCourse.php');
		}
		else if($view == 'core')
		{
			$courses = $model->getCourses();
			$sections = $model->getClassSectionNumbers(
					$courses[0]['cAbbrev'], $semesters[0]['semesterId']);
		
			include('view/reportsCore.php');
		}
		else if($view == 'outcome')
		{
			$outcomes = $model->getOutcomes();
			
			include('view/reportsOutcome.php');
		}
		else if($view == 'matrix')
		{
			include('view/reportsMatrix.php');
		}
		else if($view == 'table')
		{
			include('view/reportsTable.php');
		}
		else
		{
			include('view/reportsFaq.php');
		}
	}
	else
	{
		include('view/reportsFaq.php');
	}
?>