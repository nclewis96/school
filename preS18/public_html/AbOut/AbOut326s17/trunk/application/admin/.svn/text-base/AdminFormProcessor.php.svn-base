<?php
/** 
* Administrator form processor - processes data that user inputs into forms and
*  modifies model based on the input
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	
	//filter function to pull out the outcomes in the POST data
	function outcomeFilter($var)
	{
		if(strpos($var, 'CAC') !== FALSE || strpos($var, 'EAC') !== FALSE)
			return TRUE;
		return FALSE;
	}
	
	include('model/AdminModel.php');
	$model = new AdminModel($DB_Read, $DB_Write);
	
	if(isset($_POST['tree']))
		$_SESSION['adminTree'] = $_POST['tree'];
	
	if(isset($_POST['userId']))
	{
		$userId = intval($_POST['userId']);
		$active = isset($_POST['active']) ? 1 : 0;
		
		if($userId == -1)
		{
			$userId = $model->addUser($_POST['username'], $_POST['name'], $active);
			header("Location: AdminController.php?view=user&user=$userId&action=addUser");
		}
		else if(isset($_POST['delete']))
		{
			$model->deleteUser($userId);
			header('Location: AdminController.php?action=deleteUser');
		}
		else
		{
			$model->updateUser($userId, $_POST['username'], $_POST['name'], $active);
			header("Location: AdminController.php?view=user&user=$userId&action=updateUser");
		}
	}
	else if(isset($_POST['defaultSemester']))
	{
		$model->setDefaultSemester($_POST['defaultSemester']);
		header('Location: AdminController.php?view=semester&action=setDefaultSemester');
	}
	else if(isset($_POST['semester']))
	{
		$semesterId = $model->addSemester($_POST['semester']);
		if(isset($_POST['default']))
			$model->setDefaultSemester($semesterId);
		
		header('Location: AdminController.php?view=semester&action=addSemester');
	}
	else if(isset($_POST['outcome']))
	{
		$outcome = $_POST['outcome'];
		
		if($outcome == -1)
		{
			$outcomeName = $_POST['outcomePrefix'].' '.$_POST['outcomeName'];
			$model->addOutcome($outcomeName, $_POST['outcomeDescription'],
					$_POST['program'], $_POST['start'], $_POST['end']);
			header("Location: AdminController.php?view=outcome&outcome=$outcomeName&action=addOutcome");
		}
		else if(isset($_POST['delete']))
		{
			$model->deleteOutcome($outcome);
			header('Location: AdminController.php?action=deleteOutcome&action=deleteOutcome');
		}
		else
		{
			$model->updateOutcome($outcome, $_POST['outcomeDescription'],
					$_POST['program'], $_POST['start'], $_POST['end']);
			header("Location: AdminController.php?view=outcome&outcome=$outcome&action=updateOutcome");
		}
	}
	else if(isset($_POST['courseId']))
	{
		$courseId = $_POST['courseId'];
		$outcomes = array_filter($_POST, 'outcomeFilter');
		$csFlag = isset($_POST['cs']) ? 1 : 0;
		$seFlag = isset($_POST['se']) ? 1 : 0;
		
		if(isset($_POST['reset']))
		{
			header("Location: AdminController.php?view=course&course=$courseId&action=reset");
		}
		else if($courseId == -1)
		{
			$courseId = $_POST['cAbbrev'].' '.$_POST['cNumber'];
			$model->addCourse($courseId, $_POST['courseName'], $csFlag, 
					$seFlag, $_POST['start'], $_POST['end'], $outcomes);
			header("Location: AdminController.php?view=course&course=$courseId&action=addCourse");
		}
		else if(isset($_POST['delete'] ))
		{
			
			$model->deleteCourse($courseId);
			header('Location: AdminController.php?action=deleteCourse');
		}
		else
		{
			$model->updateCourse($courseId, $_POST['courseName'], $csFlag, 
					$seFlag, $_POST['end'], $outcomes);
			header("Location: AdminController.php?view=course&course=$courseId&action=updateCourse");
		}
	}
	else if(isset($_POST['offeringId']))
	{
		
		/** 
		* Returns a array of students in file $filename
		* @param $filename - filename containing a list of students
		* @return Array of student names
		*/
		function importFile($filename)
		{
			$file = fopen($filename,'r') or exit('Unable to open file.');
			$students = array();
			while(!feof($file))
			{
				$line = fgets($file);
				$line = trim($line);
				$line = str_replace('"', '', $line);
				
				if(strlen($line) > 0)
				{
					array_push($students, $line);
				}
			}
			return $students;
		}
	
		$offeringId = $_POST['offeringId'];
		
		if(isset($_POST['import']) 
			&& $_FILES['file']['error'] == UPLOAD_ERR_OK 
			&& is_uploaded_file($_FILES['file']['tmp_name']))
		{
			$students = importFile($_FILES['file']['tmp_name']);
		}
		else if(isset($_POST['add']))
		{
			$students = array($_POST['student']);
		}
		
		if($offeringId == -1)
		{
			$offeringId = $model->addOffering($_POST['course'], $_POST['single'], $_POST['section'], $_POST['user']);
			if(!isset($_POST['save']))
			{
				$model->addStudentsToOffering($offeringId, $students);
			}
			
			header("Location: AdminController.php?view=offering&offering=$offeringId&action=addOffering");
		}
		else if(isset($_POST['remove']))
		{
			$studentId = array_flip($_POST['remove'])['Remove'];
			$model->removeStudentFromOffering($studentId, $offeringId);
			header("Location: AdminController.php?view=offering&offering=$offeringId&action=removeStudentFromOffering");
		}
		else if(isset($_POST['removeAll']))
		{
			$model->removeAllStudentsFromOffering($offeringId);
			header("Location: AdminController.php?view=offering&offering=$offeringId&action=removeAllStudentsFromOffering");
		}
		else if(isset($_POST['delete']))
		{
			$model->deleteOffering($offeringId);
			header('Location: AdminController.php?action=deleteOffering');
		}
		else
		{
			$model->updateOffering($offeringId, $_POST['section'], $_POST['user']);
		
			if(!isset($_POST['save']))
			{
				$model->addStudentsToOffering($offeringId, $students);
			}
			
			header("Location: AdminController.php?view=offering&offering=$offeringId&action=updateOffering");
		}
	}
	else//no post data that we're looking for so redirect to home
	{
		header('Location: AdminController.php');
	}
?>