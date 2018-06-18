<?php
/** 
* Interacts with CAS to authenticate user
*/

	include_once('CAS.php');
	
	phpCAS::setDebug();
	
	// Old CAS: 
	//phpCAS::client(CAS_VERSION_2_0, 'mtctsgrn.mtech.edu', 443, 'cas');
	phpCAS::client(CAS_VERSION_2_0, 'mtlbcas.mtech.edu', 443, 'cas');
	
	// For quick testing you can disable SSL validation of the CAS server.
	// THIS SETTING IS NOT RECOMMENDED FOR PRODUCTION.
	// VALIDATING THE CAS SERVER IS CRUCIAL TO THE SECURITY OF THE CAS PROTOCOL!
	phpCAS::setNoCasServerValidation();
	
	if(isset($_POST['logout']))
	{
		session_destroy();
		phpCAS::logout();
	}
	else if(isset($_POST['login']))
	{
		phpCAS::forceAuthentication();
	}
	else if(phpCAS::checkAuthentication())
	{
		$model = new LoginModel($DB_Read, $DB_Write);
		$result = $model->getUser(phpCAS::getUser());
		$_SESSION['usernameCAS'] = phpCAS::getUser();
		
		if(!empty($result))
		{
			//$_SESSION['loggedIn'] = true; dont think this is necessary since the other vars being set tells us that the user is logged in
			$_SESSION['username'] = $result['uName'];
			$_SESSION['userId'] = $result['userId'];
			$_SESSION['isActive'] = $result['activeFlag'];//flag defines if the user is admin or faculty
			$_SESSION['semesterId'] = $model->getDefaultSemester();
			$_SESSION['semester'] = $model->getSemester($_SESSION['semesterId']);
		}
	}
	//else the user didn't ask to login or logout so do nothing
?>