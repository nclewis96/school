<?php
/** 
* Faculty REST API - controls view and provides interface for AJAX
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');
	
	if(!isset($model))
	{
		include('model/FacultyModel.php');
		$model = new FacultyModel($DB_Read, $DB_Write);
	}
	
	if(isset($_GET['view']))
	{
		$view = $_GET['view'];
		
		if($view === 'offering')
		{
			$offeringId = $_GET['offering'];
			
			$offeringInfo = $model->getOfferingInformation($offeringId);
			
			$courseAbbrev = $offeringInfo['cAbbrev'];
			$sectionNo = $offeringInfo['sectionNo'];
			$name = $offeringInfo['fName'];
			$semesterId = $offeringInfo['semesterId'];
			
			$semester = $model->getSemester($semesterId);
			$courseName = $model->getCourseName($courseAbbrev);
			$outcomes = $model->getCourseOutcomes($offeringId);
			$students = $model->getStudentsForOffering($offeringId);
			
			$head = "Edit Offering - $courseAbbrev $courseName";
		
			include('view/facultyOffering.php');
		}
		else if($view === 'assessment')
		{
			$assessId = $_GET['assessment'];
			$head = 'Add Assessment';
			
			if($assessId > -1)
			{
				$assessmentInfo = $model->getAssessmentInformation($assessId);
			
				$desc = $assessmentInfo['description'];
				$maxPoints = $assessmentInfo['maxPoints'];
				$offeringId = $assessmentInfo['offeringId'];
				
				$head = 'Edit Assessment - '.$desc;
			}
			else
			{
				$desc = '';
				$maxPoints = '';
				$offeringId = $_GET['offering'];
			}
			
			$offeringInfo = $model->getOfferingInformation($offeringId);
			
			$courseAbbrev = $offeringInfo['cAbbrev'];
			$sectionNo = $offeringInfo['sectionNo'];
			$name = $offeringInfo['fName'];
			$semesterId = $offeringInfo['semesterId'];
			
			$assessmentOutcomes = $model->getOutcomesForAssessment($assessId);
			$semester = $model->getSemester($semesterId);
			$courseName = $model->getCourseName($courseAbbrev);
			$outcomes = $model->getCourseOutcomes($offeringId);
			$students = $model->getStudentsForOffering($offeringId);
			
			include('view/facultyAssessment.php');
		}
		else
		{
			include('view/facultyFaq.php');
		}
	}
	else
	{
		include('view/facultyFaq.php');
	}
?>
