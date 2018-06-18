<?php
/** 
* Reports controller - sets up page using html files and widgets
*  and controls view
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
	$title   = 'AbOut - Reports';
	
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
	echo '<div class="colmask leftmenu"><div class="colleft">';
	include('view/reportsTree.php');
	include('ReportsREST.php');
	
	echo '</div></div>';
	
	$html = explode('{FOOTER}', $html);
	echo $html[0];
	$html = $html[1];
	include(INCLUDE_PATH.'footer.php');
	echo $html;
?>
