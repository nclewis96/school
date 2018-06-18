<?php
/** 
* Faculty controller - sets up page using html files and widgets, 
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
	$title   = 'AbOut - Faculty';
	
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
	include('model/FacultyModel.php');
	
	echo '<div class="colmask leftmenu"><div class="colleft">';

//check if an action was done: save, delete,..
	if(!empty($_GET['action']))
	{
		$msg = '';
		
		switch($_GET['action'])
		{
		case 'save':
			$msg = "Assessment was successfully saved";
			break;
		case 'delete':
			$msg = "Assessment was successfully deleted";
			break;
		case 'reset':
			$msg = "Assessment was successfully reset";
			break;
		case 'add':
			$msg = "Student was successfully added";
			break;
		case 'remove':
			$msg = "Student was successfully removed";
			break;
		}
		
		echo "<script type='text/javascript'>informAction('$msg');</script>";
	}
	
	$model = new FacultyModel($DB_Read, $DB_Write);
	$userId = $_SESSION['userId'];
	$semesters = $model->getSemestersTaught($userId);
	
	include('view/facultyTree.php');
	include('FacultyREST.php');

	echo '</div></div>';
	
	$html = explode('{FOOTER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'footer.php');
	echo $html;
?>
