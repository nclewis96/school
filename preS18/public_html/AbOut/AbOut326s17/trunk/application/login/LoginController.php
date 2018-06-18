<?php
/** 
* Login controller - sets up page using html files, responsible for
*  logging in user
*/

	require_once('../includes/Bootstrap.php');
	require_once(INCLUDE_PATH.'startup.php');
	require_once(INCLUDE_PATH.'HTTPBootstrap.php');
	
	include('model/LoginModel.php');
	include('CASRedirect.php');
	
	if(isset($_SESSION['username']))
	{
		header('Location: '.HTTP_BASE_PATH.'index.php');
		die(); //after redirect the code following will continue so kill it
	}
	
	$html    = file_get_contents(HTML_PATH.'empty.html');
	$meta   = file_get_contents(HTML_PATH.'meta.html');
	$styles  = str_replace('{STYLES_PATH}', HTTP_STYLES_PATH, file_get_contents(HTML_PATH.'styles.html'));
	$scripts = str_replace('{SCRIPT_PATH}', HTTP_SCRIPT_PATH, file_get_contents(HTML_PATH.'scripts.html'));
	
	$replaceTags = array('{META}', '{STYLES}', '{SCRIPTS}', '{TITLE}');
	$replacement = array($meta   , $styles   , $scripts   , 'AbOut Login');
	$html = str_replace($replaceTags, $replacement, $html);
	
	$html = explode('{HEADER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'header.php');
	$html = explode('{BODY}', $html);
	echo $html[0];
	$html = $html[1];
	
	//control logic
	if(isset($_SESSION['usernameCAS']))
	{
		session_destroy();
		phpCAS::logout();//cas redirect is broken so it 
		//explain to the user that they need to be added to the AbOut database
		include('view/loginNotice.php');
	}
	else
	{
		include('view/loginWelcome.php');
	}
	
	$html = explode('{FOOTER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'footer.php');
	echo $html;
?>
