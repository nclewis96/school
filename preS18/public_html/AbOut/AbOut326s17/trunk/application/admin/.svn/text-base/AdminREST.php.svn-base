<?php
/** 
* Administrator REST API - controls view and provides interface for AJAX
*/

	require_once('../includes/Bootstrap.php');
	include_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');
	
	if(!isset($model))
	{
		include('model/AdminModel.php');
		$model = new AdminModel($DB_Read, $DB_Write);
		
		$courses = $model->getCourses();
		$outcomes = $model->getOutcomes();
		$users = $model->getUsers();
	}
	
	if(isset($_GET['request']))
	{
		$request = $_GET['request'];
		if($request == 'deleteCourse')
		{
			$course = $_GET['course'];
			$numOfferings = count($model->getOfferings($course));
			echo $numOfferings."\xA";
		}
		else if ($request == 'checkOffering')
		{
			$course = $_GET['course'];
			$sem = $_GET['semester'];
			$section = $_GET['section'];
			
			$numOfferings = $model->getCourseOffering($course, $sem, $section);
			echo $numOfferings."\xA";
		}
	}
	else if(isset($_GET['view']))
	{
		$view = $_GET['view'];
		
		if($view == 'course')
		{
			$course = $_GET['course'];
			$head = 'Add Course';
			$courseName = '';
			
			$csOutcomes = $model->getCSOutcomes();
			$seOutcomes = $model->getSEOutcomes();
			
			$csFlag = 0;
			$seFlag = 0;
			
			if($course != -1)//while course is a string php will auto convert it to an int
			{
				$courseInfo = $model->getCourse($course);
				$courseName = $courseInfo['cName'];
				$csFlag = $courseInfo['csFlag'];
				$seFlag = $courseInfo['seFlag'];
				
				$semester = $model->getSemester($courseInfo['beginSem']);
				$semesters = $model->getSemestersGreaterThan($courseInfo['beginSem']);
				$outcomes = $model->getCourseOutcomes($course);
				
				$head = "Edit Course - $course $courseName";
			}
			else
			{
				$prefixes = $model->getCoursePrefixes();
				$semesters = $model->getSemesters();
			}
		
		
			include('view/adminCourse.php');
		}
		else if($view == 'offering')
		{
			$offering = $_GET['offering'];
			
			if($offering > -1)
			{
				$offeringInfo = $model->getOffering($offering);
				$course = $offeringInfo['cAbbrev'];
				$semesterId = $offeringInfo['semesterId'];
				$sectionNo = $offeringInfo['sectionNo'];
				$userId = $offeringInfo['userId'];
				
				$courseInfo = $model->getCourse($course);
				$courseName = $courseInfo['cName'];
				
				$semester = $model->getSemester($semesterId);
				$users = $model->getUsers();
				$outcomeAbbrevs = $model->getCourseOutcomes($course);
				$outcomes = $model->getOutcomes();
				$students = $model->getStudentsForOffering($offering);
				
				$head = "Edit Offering - $course $courseName";
			}
			else
			{
				$course = $_GET['course'];
				$outcomeAbbrevs = $model->getCourseOutcomes($course);
				
				$courseInfo = $model->getCourse($course);
				$courseName = $courseInfo['cName'];
				$semesterId = $courseInfo['beginSem'];
				$sectionNo = '01';
				
				$semesters = $model->getSemestersGreaterThan($semesterId);
				
				$students = array();
				$userId = 0;
				
				$head = "Add Offering - $course $courseName";
			}
			
			include('view/adminOffering.php');
		}
		else if($view == 'outcome')
		{
			$outcome = $_GET['outcome'];
			$head = 'Add Outcome';
			
			$oText = '';
			$semesters = $model->getSemesters();
			$beginSem = -1;
			$endSem = -1;
			$pAbbrev = '';
			
			if($outcome != -1)
			{
				$outcomeInfo = $model->getOutcome($outcome);
				$oText = $outcomeInfo['oText'];
				$beginSem = $outcomeInfo['beginSem'];
				$endSem = $outcomeInfo['endSem'];
				$pAbbrev = $outcomeInfo['pAbbrev'];
				
				$head = "Edit Outcome - $outcome";
			}
			else
			{
				$prefixes = $model->getOutcomePrefixes();
			}
			
			include('view/adminOutcome.php');
		}
		else if($view == 'semester')
		{
			$action = $_GET['action'];
			
			$semesters = $model->getSemesters();
			$defaultId = $model->getDefaultSemester();
			
			if($action == 'add')
			{
				$semester = $model->getCurrentSemester();
				
				$semester = explode(' ', $semester);
				
				$season = $semester[0];
				$year = $semester[1];
				
				if($season == 'Fall')
				{
					$year++;
					$season = 'Spring';
				}
				else if($season == 'Spring')
				{
					$season = 'Summer';
				}
				else
				{
					$season = 'Fall';
				}
				
				include('view/adminSemesterAdd.php');
			}
			else if($action == 'default')
			{
				
				include('view/adminSemesterDefault.php');
			}
			else //if $action == 'list'
			{
				include('view/adminSemesterList.php');
			}
		}
		else if($view == 'user')
		{
			$user = $_GET['user'];
			$head = 'Add User';
			
			if($user > -1)
			{
				$userInfo = $model->getUser($user);
				$uName = $userInfo['uName'];
				$username = $userInfo['usernameCAS'];
				$active = $userInfo['activeFlag'] == 1;
				$head = "Edit User - $uName";
			}
			
			include('view/adminUser.php');
		}
		else
		{
			include('view/adminFaq.php');
		}
	}
	else
	{
		include('view/adminFaq.php');
	}
?>
