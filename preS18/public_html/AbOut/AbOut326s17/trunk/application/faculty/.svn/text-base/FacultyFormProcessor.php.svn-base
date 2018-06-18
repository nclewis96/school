<?php
/** 
* Faculty form processor - processes data that user inputs into forms and
*  modifies model based on the input
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');

	//filter function to pull out the outcomes in the POST data
	function outcomeFilter($var)
	{
		if(strpos($var, 'CAC') !== FALSE || strpos($var, 'EAC') !== FALSE)
			return TRUE;
		return FALSE;
	}
	
	include('model/FacultyModel.php');
	$model = new FacultyModel($DB_Read, $DB_Write);
	
	if(isset($_POST['tree']))
		$_SESSION['facultyTree'] = $_POST['tree'];
	
	if(isset($_POST['assessId']))
	{
		$assessId = $_POST['assessId'];
		$offeringId = $_POST['offeringId'];
		$desc = $_POST['asDesc'];
		$maxPoints = $_POST['maxText'];
		
		$outcomes = array_filter($_POST, 'outcomeFilter');
		$students = array();
		foreach($_POST as $key=>$value)
		{
			if(strpos($key, 'student') === 0)
			{
				$students[str_replace('student', '', $key)] = $value;
			}
		}
	
		if(isset($_POST['save']))
		{
			if($assessId < 0)
			{
				$assessId = $model->insertAssessment($desc, $maxPoints, $offeringId);
				
				foreach($students as $key=>$value)
				{
					$model->insertAssessmentScore($assessId, $key, $value);
				}
			}
			else
			{
				$model->updateAssessment($assessId, $desc, $maxPoints);
				
				foreach($students as $key=>$value)
				{
					$model->updateAssessmentScore($assessId, $key, $value);
				}
				
				$model->deleteAssessmentOutcomes($assessId);
			}
			
			foreach($outcomes as $outcome)
			{
				$model->insertAssessmentOutcome($assessId, $outcome);
			}
			
			header("Location: FacultyController.php?view=assessment&assessment=$assessId&action=save");
		}
		else if(isset($_POST['delete']))
		{
			$model->deleteAssessmentScores($assessId);
			$model->deleteAssessmentOutcomes($assessId);
			$model->deleteAssessment($assessId);
		
			header("Location: FacultyController.php?view=offering&offering=$offeringId&action=delete");
		}
		else //if(isset($_POST['reset'])
		{
			if($assessId < 0)
				header("Location: FacultyController.php?view=assessment&assessment=$assessId&offering=$offeringId&action=reset");
			else
				header("Location: FacultyController.php?view=assessment&assessment=$assessId&action=reset");
		}
	}
	else
	{
		$offeringId = $_POST['offeringId'];
		
		if(isset($_POST['remove']))
		{
			$studentId = array_flip($_POST['remove'])['Remove'];
			$model->deleteStudent($studentId);
			
			header("Location: FacultyController.php?view=offering&offering=$offeringId&action=remove");
		}
		else if(isset($_POST['addAssessment']))
		{
			header("Location: FacultyController.php?view=assessment&assessment=-1&offering=$offeringId");
		}
		else if(isset($_POST['report']))
		{
			$offeringInfo = $model->getOfferingInformation($offeringId);
			$_SESSION['post'] = array();
			$_SESSION['post']['raw'] = 'no';
			$_SESSION['post']['view'] = 'core';
			$_SESSION['post']['csv'] = 'on';
			$_SESSION['post']['course'] = $offeringInfo['cAbbrev'];
			$_SESSION['post']['section'] = $offeringInfo['sectionNo'];
			$_SESSION['post']['semester'] = $offeringInfo['semesterId'];
			header("Location: ".HTTP_REPORTS_PATH."ReportsFormProcessor.php");
		}
		else if(isset($_POST['add']))
		{
			//add student to the offering
			$name = $_POST['addStudent'];
			
			$studentId = $model->insertStudent($name, $offeringId);
			$assessmentIds = $model->getAssessmentIds($offeringId);
			
			foreach($assessmentIds as $id)
			{
				$model->insertAssessmentScore($id[0], $studentId, 0);
			}
			
			header("Location: FacultyController.php?view=offering&offering=$offeringId&action=add");
		}
		else if(isset($_POST['export']))
		{
			//export student list
			header('Content-Type: text/csv; charset=utf-8');
			header('Content-Disposition: attachment; filename=studentList.csv');
			
			$output = fopen('php://output', 'w');
			$students = $model->getStudentNames($offeringId);
			
			foreach($students as $student)
			{
				fputcsv($output, array($student['sName']));
			}
		}
		else //unknown command go back to the offering
		{
			header("Location: FacultyController.php?view=offering&offering=$offeringId");
		}
	}
?>
