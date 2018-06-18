<?php
/** 
* Administrator controller - sets up page using html files and widgets, 
*  gives feedback based on user action
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');
	
	//if not logged in send them back to the welcome screen
	if(!isset($_SESSION['username']))
	{
		header('Location: ../index.php');
	}
	
	$html    = file_get_contents(HTML_PATH.'empty.html');
	$meta    = file_get_contents(HTML_PATH.'meta.html');
	$styles  = str_replace('{STYLES_PATH}', HTTP_STYLES_PATH, file_get_contents(HTML_PATH.'styles.html'));
	$scripts = str_replace('{SCRIPT_PATH}', HTTP_SCRIPT_PATH, file_get_contents(HTML_PATH.'scripts.html'));
	$title   = 'AbOut - Admin';
	
	$replaceTags = array('{META}', '{STYLES}', '{SCRIPTS}', '{TITLE}');
	$replacement = array($meta   , $styles   , $scripts   , $title);
	$html = str_replace($replaceTags, $replacement, $html);
	
	$html = explode('{HEADER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'header.php');
	$html = explode('{BODY}', $html);
	echo $html[0];
	$html = $html[1];
	
	//include body files here
	include(INCLUDE_PATH.'widgets/tabsWidget.php');
	include('model/AdminModel.php');
	
	echo '<div class="colmask leftmenu"><div class="colleft">';
	
	$model = new AdminModel($DB_Read, $DB_Write);
	
	$courses = $model->getCourses();
	$outcomes = $model->getOutcomes();
	$users = $model->getUsers();
	
	include('view/adminTree.php');
	
//check if an action was done: save, delete,..
	if(!empty($_GET['action']))
	{
		$msg = '';
	
		switch($_GET['action'])
		{
		case "updateOffering":
			$msg = "Offering was successfully updated";
			break;
		case "deleteOffering":
			$msg = "Offering was successfully deleted";
			break;
		case "removeStudentFromOffering":
			$msg = "Student was successfully removed from offering";
			break;
		case "removeAllStudentsFromOffering":
			$msg = "All students were successfully removed from offering";
			break;
		case "addOffering":
			$msg = "Offering was successfully added";
			break;
		case "updateCourse":
			$msg = "Course was successfully updated";
			break;
		case "addCourse":
			$msg = "Course was successfully added";
			break;
		case "deleteCourse":
			$msg = "Course was successfully deleted";
			break;
		case "reset":
			$msg = "Course was successfully reset";
			break;
		case "addOutcome":
			$msg = "Outcome was successfully added";
			break;
		case "deleteOutcome":
			$msg = "Outcome was successfully deleted";
			break;
		case "updateOutcome":
			$msg = "Outcome was successfully updated";
			break;
		case "addSemester":
			$msg = "A semester was successfully added";
			break;
		case "setDefaultSemester":
			$msg = "Default semester was successfully added";
			break;
		case "addUser":
			$msg = "A user was successfully added";
			break;
		case "deleteUser":
			$msg = "A user was successfully deleted";
			break;
		case "updateUser":
			$msg = "A user was successfully updated";
			break;
		case "cancel":
			$msg = "Action was successfully cancelled";
			break;
		}

		echo "<script type='text/javascript'>informAction('$msg');</script>";
	}
	
	include('AdminREST.php');
	
	echo '</div></div>';
	
	$html = explode('{FOOTER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'footer.php');
	echo $html;
?>
