<?php
/** 
* PHP Bootstrap - facilitates folder navigation by setting variables to
*  different file locations
*/

	define('BASE_PATH'   , dirname(__DIR__).'/'   ); //!< application root directory: note this file is not in the root directory  
	define('ADMIN_PATH'  , BASE_PATH.'admin/'     ); //!< admin directory
	define('FACULTY_PATH', BASE_PATH.'faculty/'   ); //!< faculty directory
	define('REPORTS_PATH', BASE_PATH.'reports/'   ); //!< reports directory
	define('LOGIN_PATH'  , BASE_PATH.'login/'     ); //!< login directory
	define('INCLUDE_PATH', BASE_PATH.'includes/'  ); //!< useful support classes
	define('SCRIPT_PATH' , BASE_PATH.'javascript/'); //!< javascript files location
	define('STYLES_PATH' , BASE_PATH.'css/'       ); //!< cascading style sheet files location
	define('HTML_PATH'   , BASE_PATH.'html/'      ); //!< html file location
	define('IMAGE_PATH'  , BASE_PATH.'images/'    ); //!< image file location
?>
