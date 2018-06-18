<?php

	/** 
	* Login Model - retrieves information from database
	*/
	class LoginModel
	{
		private $dbRead;
		private $dbWrite;
		
		/** 
		* Constructor - sets PDO variables for database connection
		* @param $DB_READ - database read PDO object
		* @param $DB_WRITE - database write PDO object
		*/
		public function __construct($read, $write)
		{
			$this->dbRead = $read;
			$this->dbWrite = $write;
		}
		
		/** 
		* Get user information for user with CAS user name $user
		* @param $user - CAS user name
		* @return User information for user with CAS user name $user
		*/			
		public function getUser($user)
		{
			$stmt = $this->dbRead->prepare("SELECT userId, uName, activeFlag FROM User WHERE usernameCAS = LCASE('$user');");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get the semester ID of the default semester
		* @return semester ID of the default semester
		*/			
		public function getDefaultSemester()
		{
			$stmt = $this->dbRead->prepare("SELECT semesterId FROM DefaultSemester;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semesterId'];
		}
		
		/** 
		* Get the semester name for semester $semesterId
		* @param $semesterId - semester ID
		* @return Semester name for semester $semesterId
		*/	
		public function getSemester($semesterId)
		{
			$stmt = $this->dbRead->prepare("SELECT semester FROM Semester WHERE semesterId = $semesterId;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semester'];
		}
	}
?>