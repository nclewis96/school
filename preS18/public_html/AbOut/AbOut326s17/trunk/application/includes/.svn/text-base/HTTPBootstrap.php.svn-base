<?php
/** 
* HTTP Bootstrap - facilitates folder navigation by setting variables to
*  different file locations
*/
	//FOR THE LOVE OF GOD AND ALL THAT IS HOLY DO NOT MOVE THIS FILE 
	//IT MUST BE IN THE includes DIRECTORY

	//THESE PATHS ARE ONLY FOR HTML TAG ADDRESSES IF YOUR TRYING TO INCLUDE A FILE USE Bootstrap.php
	$string = str_replace('/includes/HTTPBootstrap.php', '', __FILE__);
	$string = explode('/', $string);

	if(PRODUCTION)
		array_pop($string);

	$string = array_pop($string);
	
	$path = explode('/', $_SERVER['SCRIPT_NAME']);
	while(count($path) > 0 && $path[count($path)-1] != $string)
		array_pop($path);
	$path = implode('/', $path).'/';

	define('HTTP_BASE_PATH'   , $path                       ); //!< application root directory: note this file is not in the root directory  
	define('HTTP_ADMIN_PATH'  , HTTP_BASE_PATH.'admin/'     ); //!< admin directory
	define('HTTP_FACULTY_PATH', HTTP_BASE_PATH.'faculty/'   ); //!< faculty directory
	define('HTTP_REPORTS_PATH', HTTP_BASE_PATH.'reports/'   ); //!< reports directory
	define('HTTP_LOGIN_PATH'  , HTTP_BASE_PATH.'login/'     ); //!< login directory
	define('HTTP_INCLUDE_PATH', HTTP_BASE_PATH.'includes/'  ); //!< useful support classes
	define('HTTP_SCRIPT_PATH' , HTTP_BASE_PATH.'javascript/'); //!< javascript files location
	define('HTTP_STYLES_PATH' , HTTP_BASE_PATH.'css/'       ); //!< cascading style sheet files location
	define('HTTP_HTML_PATH'   , HTTP_BASE_PATH.'html/'      ); //!< html file location
	define('HTTP_IMAGE_PATH'  , HTTP_BASE_PATH.'images/'    ); //!< image file location
	
	//cleanup temporary variables
	unset($path);
	unset($string);
?>
