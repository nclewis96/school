<?php

	/** 
	* Administrator Model - retrieves information from database
	*/
	class AdminModel
	{
		private $dbRead;
		private $dbWrite;
		
		/** 
		* Constructor - sets PDO variables for database connection
		* @param $DB_READ - database read PDO object
		* @param $DB_WRITE - database write PDO object
		*/
		public function __construct($DB_Read, $DB_Write)
		{
			$this->dbRead = $DB_Read;
			$this->dbWrite = $DB_Write;
		}
		
		/** 
		* Get a list of all courses in the DB
		* @return Array of all courses
		*/
		public function getCourses()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev, cName FROM Course ORDER BY cAbbrev;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all offerings associated with course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Array of all offerings of $cAbbrev
		*/
		public function getOfferings($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT semester, sectionNo, offeringId
				FROM Offering JOIN Semester ON Offering.semesterID = Semester.semesterID
				WHERE Offering.cAbbrev = '$cAbbrev';");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of all outcomes in the DB
		* @return Array of all outcomes
		*/
		public function getOutcomes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev, oText FROM Outcome ORDER BY oAbbrev;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all users in the DB
		* @return Array of all users
		*/
		public function getUsers()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT uName, userId FROM User ORDER BY uName;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of all semesters in the DB
		* @return Array of all semesters
		*/		
		public function getSemesters()
		{
			$stmt = $this->dbRead->prepare("SELECT * FROM Semester ORDER BY semesterId DESC;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get course information for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Course information for course $cAbbrev
		*/	
		public function getCourse($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Course WHERE cAbbrev = '$cAbbrev';");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get the semester name for semester $semesterId
		* @param $semesterId - semester ID
		* @return Semester name for semester $semesterId
		*/	
		public function getSemester($semesterId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT semester FROM Semester WHERE semesterId = $semesterId;");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semester'];
		}
		
		/** 
		* Get a list of semesters later than semester $semesterId
		* @param $semesterId - semester ID
		* @return Array of semesters later than semester $semesterId
		*/	
		public function getSemestersGreaterThan($semesterId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT semesterId, semester FROM Semester WHERE semesterId >= $semesterId ORDER BY semesterId DESC;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all CS Outcomes in the DB
		* @return Array of CS Outcomes
		*/	
		public function getCSOutcomes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Outcome WHERE pAbbrev = 'CS';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of all SE Outcomes in the DB
		* @return Array of SE Outcomes
		*/	
		public function getSEOutcomes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Outcome WHERE pAbbrev = 'SE';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all outcomes for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Array of outcomes associated with course $cAbbrev
		*/	
		public function getCourseOutcomes($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev FROM CourseOutcome WHERE cAbbrev = '$cAbbrev';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			
			for($i = 0; $i < count($result); $i++)
			{
				$result[$i] = $result[$i][0];
			}
			
			return $result;
		}

		/** 
		* Get offering information for offering $offeringId
		* @param $offeringId - offering ID
		* @return Offering information for offering $offeringId
		*/	
		public function getOffering($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Offering WHERE offeringId = $offeringId;");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get a list of students in offering $offeringId
		* @param $offeringId - offering ID
		* @return Array of students in offering $offeringId
		*/	
		public function getStudentsForOffering($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT studentId, sName FROM Student WHERE offeringId = $offeringId ORDER BY sName;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get outcome information for outcome $outcome
		* @param $outcome - outcome abbreviation
		* @return Outcome information for outcome $outcome
		*/	
		public function getOutcome($outcome)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Outcome WHERE oAbbrev = '$outcome';");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get the name of the current semester
		* @return Name of current semester
		*/	
		public function getCurrentSemester()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT semester FROM Semester ORDER BY semesterId DESC LIMIT 1;");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semester'];
		}

		/** 
		* Get user information for user $userId
		* @param $userId - user ID
		* @return User information for user $userId
		*/			
		public function getUser($userId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT uName, usernameCAS, activeFlag FROM User WHERE userId = $userId;");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}

		/** 
		* Set the default semester to semester $semesterId
		* @param $semeseterId - semester ID
		*/			
		public function setDefaultSemester($semesterId)
		{
			$stmt = $this->dbWrite->prepare(
				"UPDATE DefaultSemester SET semesterId = $semesterId;");
			
			$stmt->execute();
		}

		/** 
		* Get the semester ID of the default semester
		* @return semester ID of the default semester
		*/			
		public function getDefaultSemester()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT semesterId FROM DefaultSemester");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semesterId'];
		}

		/** 
		* Add semester with name $name to the DB
		* @param $name - semester name
		* @return semester ID of the added semester
		*/			
		public function addSemester($name)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Semester (semester) VALUE ('$name');");
			
			$stmt->execute();
			$stmt = $this->dbRead->prepare(
				"SELECT semesterId FROM Semester WHERE semester = '$name';");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semesterId'];
		}
		
		/** 
		* Delete semester with abbreviation $outcome
		* @param $outcome - outcome abbreviation
		*/	
		public function deleteOutcome($outcome)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Outcome WHERE oAbbrev = '$outcome';");
			
			$stmt->execute();
		}
		
		/** 
		* Add an outcome to the DB
		* @param $oAbbrev - outcome abbreviation
		* @param $oText - outcome text
		* @param $pAbbrev - program abbreviation
		* @param $begin - begin semester
		* @param $end - end semester
		*/	
		public function addOutcome($oAbbrev, $oText, $pAbbrev, $begin, $end)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Outcome (oAbbrev, oText, pAbbrev, beginSem, endSem)
				VALUE ('$oAbbrev', '$oText', '$pAbbrev', $begin, $end);");
			
			$stmt->execute();
		}
		
		/** 
		* Update outcome $oAbbrev
		* @param $oAbbrev - outcome abbreviation
		* @param $oText - new outcome text
		* @param $pAbbrev - new program abbreviation
		* @param $begin - new begin semester
		* @param $end - new end semester
		*/
		public function updateOutcome($oAbbrev, $oText, $pAbbrev, $begin, $end)
		{
			$stmt = $this->dbWrite->prepare(
				"UPDATE Outcome 
				SET oText='$oText', pAbbrev='$pAbbrev', beginSem=$begin, endSem=$end 
				WHERE oAbbrev='$oAbbrev';");
				
			$stmt->execute();
		}

		/** 
		* Delete user $userId
		* @param $userId - user ID of user to delete
		*/
		public function deleteUser($userId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM User WHERE userId = $userId;");
			
			$stmt->execute();
		}

		/** 
		* Add a user
		* @param $username - CAS user name
		* @param $name - name of user
		* @param $active - active flag
		* @return user ID of the added user
		*/
		public function addUser($username, $name, $active)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO User (usernameCAS, uName, activeFlag) 
				VALUES ('$username', '$name', $active);");
			
			$stmt->execute();
			$stmt = $this->dbRead->prepare(
				"SELECT userId FROM User WHERE usernameCAS='$username' AND uName='$name';");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['userId'];
		}
		
		/** 
		* Update a user with user ID $userId
		* @param $userId - user ID of user to update
		* @param $username - new CAS user name
		* @param $name - new user name
		* @param $active - new active flag
		*/
		public function updateUser($userId, $username, $name, $active)
		{
			$stmt = $this->dbWrite->prepare(
				"UPDATE User 
				SET usernameCAS='$username', uName='$name', activeFlag=$active 
				WHERE userId=$userId;");
			
			$stmt->execute();
		}

		/** 
		* Add a course
		* @param $cAbbrev - course abbreviation
		* @param $cName - course name
		* @param $csFlag - CS program flag
		* @param $seFlag - SE program flag
		* @param $begin - begin semester
		* @param $end - end semester
		* @param $outcomes - array of outcomes
		*/
		public function addCourse($cAbbrev, $cName, $csFlag, $seFlag, $begin, $end, $outcomes)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Course VALUES ('$cAbbrev', '$cName', $csFlag, $seFlag, $begin, $end);");
			
			$stmt->execute();
			$this->addCourseOutcomes($cAbbrev, $outcomes);
		}
		/** 
		* Delete course $cAbbrev, assumes that all offerings of this course are deleted
		* @param $cAbbrev - course abbreviation
		*/
		public function deleteCourse($cAbbrev)
		{
			//delete outcomes then the course
			$this->deleteCourseOutcomes($cAbbrev);
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Course WHERE cAbbrev='$cAbbrev';");
			
			$stmt->execute();
		}
		
		/** 
		* Updates course $cAbbrev
		* @param $cAbbrev - course abbreviation of course to update
		* @param $cName - new course name
		* @param $csFlag - new CS program flag
		* @param $seFlag - new SE program flag
		* @param $end - new end semester
		* @param $outcomes - array of outcomes
		*/
		public function updateCourse($cAbbrev, $cName, $csFlag, $seFlag, $end, $outcomes)
		{
			$stmt = $this->dbWrite->prepare(
				"UPDATE Course
				SET cName='$cName', csFlag=$csFlag, seFlag=$seFlag, endSem=$end
				WHERE cAbbrev='$cAbbrev';");
				
			$stmt->execute();
			$this->deleteCourseOutcomes($cAbbrev);
			$this->addCourseOutcomes($cAbbrev, $outcomes);
		}
		
		/** 
		* Add course outcomes to course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @param $outcomes - array of outcomes
		*/
		private function addCourseOutcomes($cAbbrev, $outcomes)
		{
			foreach($outcomes as $outcome)
			{
				$stmt = $this->dbWrite->prepare(
					"INSERT INTO CourseOutcome VALUES ('$cAbbrev', '$outcome');");
				
				$stmt->execute();
			}
		}
		
		/** 
		* Delete all course outcomes to course $cAbbrev
		* @param $cAbbrev - course abbreviation
		*/
		private function deleteCourseOutcomes($cAbbrev)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM CourseOutcome WHERE cAbbrev='$cAbbrev';");
			
			$stmt->execute();
		}
		
		/** 
		* Add an offering 
		* @param $cAbbrev - course abbreviation
		* @param $semesterId - semester ID
		* @param $sectionNo - section number
		* @param $userId - user ID of instructor
		* @return Offering ID of added offering
		*/
		public function addOffering($cAbbrev, $semesterId, $sectionNo, $userId)
		{
			//get the user's name
			$stmt = $this->dbRead->prepare(
				"SELECT uName FROM User WHERE userId=$userId;");
			
			$stmt->execute();
			$name = $stmt->fetch(PDO::FETCH_ASSOC)['uName'];
			
			//insert the new offering
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Offering (cAbbrev, semesterId, sectionNo, userId, fName)
				VALUES ('$cAbbrev', $semesterId, '$sectionNo', $userId, '$name');");
			
			$stmt->execute();
			//get the new offering's id
			$stmt = $this->dbRead->prepare(
				"SELECT offeringId FROM Offering 
				WHERE cAbbrev='$cAbbrev' AND semesterId=$semesterId AND sectionNo='$sectionNo';");
			
			$stmt->execute();
			$offeringId = $stmt->fetch(PDO::FETCH_ASSOC)['offeringId'];
			
			$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev FROM CourseOutcome WHERE cAbbrev='$cAbbrev';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();

			foreach($result as $outcome)
			{
				$outcome = $outcome[0];
				$stmt = $this->dbRead->prepare(
					"INSERT INTO OffOutcome VALUES ($offeringId, '$outcome');");
				$stmt->execute();
			}
			
			return $offeringId;
		}
		
		/** 
		* Deletes offering $offeringId, assumes the given offering has no assessments
		* @param $offeringId - offering ID of offering to delete
		*/
		public function deleteOffering($offeringId)
		{
			$this->removeAllStudentsFromOffering($offeringId);
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM OffOutcome WHERE offeringId=$offeringId;");
			
			$stmt->execute();
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Offering WHERE offeringId=$offeringId;");
			
			$stmt->execute();
		}
		
		/** 
		* Updates offering $offeringId
		* @param $offeringId - offering ID of offering to update
		* @param $sectionNo - new section number
		* @param $userId - new user ID of instructor
		*/
		public function updateOffering($offeringId, $sectionNo, $userId)
		{
			//get the user's name
			$stmt = $this->dbRead->prepare(
				"SELECT uName FROM User WHERE userId=$userId;");
			
			$stmt->execute();
			$name = $stmt->fetch(PDO::FETCH_ASSOC)['uName'];
			$stmt = $this->dbWrite->prepare(
				"UPDATE Offering
				SET sectionNo='$sectionNo', userId=$userId, fName='$name'
				WHERE offeringId=$offeringId;");
			
			$stmt->execute();
		}
		
		/** 
		* Adds a list of students to offering $offeringId
		* @param $offeringId - offering ID
		* @param $students - array of student names to add
		*/
		public function addStudentsToOffering($offeringId, $students)
		{
			foreach($students as $student)
			{
				$stmt = $this->dbWrite->prepare(
					"INSERT INTO Student (sName, offeringId) 
					VALUES ('$student', $offeringId);");
				$stmt->execute();
			}
		}
		
		/** 
		* Removes all students from offering $offeringId
		* @param $offeringId - offering ID
		*/
		public function removeAllStudentsFromOffering($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT studentId FROM Student WHERE offeringId=$offeringId;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			foreach($result as $student)
			{
				$student = $student['studentId'];
				$this->removeStudentFromOffering($student, $offeringId);
			}
		}
		
		/** 
		* Removes student $studentId from offering $offeringId
		* @param $studentId - student ID
		* @param $offeringId - offering ID
		*/
		public function removeStudentFromOffering($studentId, $offeringId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Score WHERE studentId=$studentId;");
			
			$stmt->execute();
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Student WHERE studentId=$studentId AND offeringId=$offeringId;");
			
			$stmt->execute();
		}
		
		/** 
		* Gets a list of all course prefixes
		* @return Array of all course prefixes
		*/
		public function getCoursePrefixes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM CoursePrefix;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Gets a list of all outcome prefixes
		* @return Array of all outcome prefixes
		*/
		public function getOutcomePrefixes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM OutcomePrefix;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Returns the number of offerings defined by ($cAbbrev, $semesterId, $sectionNo)
		*  (should be at most 1, 0 if the offering does not exist)
		* @param $cAbbrev - course abbreviation
		* @param $semesterId - semester ID
		* @param $sectionNo - section number
		* @return Offering information for the offering defined by the given parameters	
		*/
		public function getCourseOffering($cAbbrev, $semesterId, $sectionNo)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Offering WHERE cAbbrev = '$cAbbrev' AND sectionNo = '$sectionNo' 
				AND semesterId = $semesterId;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return count($result);
		}
	}
?>