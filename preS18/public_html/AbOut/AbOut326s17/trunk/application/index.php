<?php
	require_once('includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');
	
	if(!isset($_SESSION['username']))
	{
		//no username redirect to login controller
		header('Location: '.HTTP_LOGIN_PATH.'LoginController.php');
	}
	else if($_SESSION['isActive'])
	{
		header('Location: '.HTTP_FACULTY_PATH.'FacultyController.php');
	}
	else
	{
		header('Location: '.HTTP_ADMIN_PATH.'AdminController.php');
	}
?>
