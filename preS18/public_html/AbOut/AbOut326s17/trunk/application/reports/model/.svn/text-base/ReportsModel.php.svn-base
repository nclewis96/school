<?php

	/** 
	* Reports Model - retrieves information from database
	*/
	class ReportsModel
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
		* Get a list of all outcome abbreviations
		* @return Array of all outcome abbreviations
		*/
		public function getOutcomes()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev FROM Outcome ORDER BY oAbbrev;");
				
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
			$stmt = $this->dbRead->prepare(
				"SELECT semesterId, semester FROM Semester ORDER BY semesterId DESC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all courses in the DB
		* @return Array of all courses
		*/
		public function getCourses()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev, cName FROM Course ORDER BY cAbbrev ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all CS Courses in the DB
		* @return Array of all CS courses
		*/	
		public function getCSCourses()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev, cName FROM Course WHERE csFlag = 1 ORDER BY cAbbrev ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of all SE Courses in the DB
		* @return Array of all SE courses
		*/	
		public function getSECourses()
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev, cName FROM Course WHERE seFlag = 1 ORDER BY cAbbrev ASC;");
				
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
				"SELECT CourseOutcome.oAbbrev, oText FROM CourseOutcome 
					JOIN Outcome ON CourseOutcome.oAbbrev = Outcome.oAbbrev 
						WHERE cAbbrev = '$cAbbrev' ORDER BY CourseOutcome.oAbbrev ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of CS outcomes for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Array of CS outcomes associated with course $cAbbrev
		*/	
		public function getCourseCSOutcomes($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT CourseOutcome.oAbbrev, oText FROM CourseOutcome 
					JOIN Outcome ON CourseOutcome.oAbbrev = Outcome.oAbbrev 
						WHERE cAbbrev = '$cAbbrev' AND pAbbrev='CS'
							ORDER BY CourseOutcome.oAbbrev ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of SE outcomes for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Array of SE outcomes associated with course $cAbbrev
		*/	
		public function getCourseSEOutcomes($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT CourseOutcome.oAbbrev, oText FROM CourseOutcome 
					JOIN Outcome ON CourseOutcome.oAbbrev = Outcome.oAbbrev 
						WHERE cAbbrev = '$cAbbrev'  AND pAbbrev='SE'
							ORDER BY CourseOutcome.oAbbrev ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		/** 
		* Get a list of all outcomes of program(s) $program
		* @param $program - "cac" for CAC, "both" for both programs, else EAC
		* @return Array of outcomes for the given program
		*/	
		public function getProgramOutcomes($program)
		{
			if ($program == "both")
			{
				$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev, oText FROM Outcome 
					ORDER BY oAbbrev ASC;");
			}
			elseif ($program == "cac")
                     {
				$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev, oText FROM Outcome WHERE pAbbrev = 'CS'
					ORDER BY oAbbrev ASC;");
			}
			else
			{
				$stmt = $this->dbRead->prepare(
				"SELECT oAbbrev, oText FROM Outcome WHERE pAbbrev = 'SE'
					ORDER BY oAbbrev ASC;");
			}
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of courses for a program(s) within a given semester range
		* @param $program - "cac" for CAC, "both" for both programs, else EAC
		* @param $start - first semester in range (inclusive)
		* @param $end - last semester in range (inclusive)
		* @return Array of courses for a program(s) within the given semester range
		*/	
		public function getProgramCoursesInRange($program, $start, $end)
		{
			if ($program == "both")
			{
				$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev from Course WHERE beginSem <= $start AND (endSem IS NULL OR endSem <= $end)
					ORDER BY cAbbrev ASC;");
			}
			else if ($program == "cac")
                     {
				$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev from Course WHERE beginSem <= $start AND (endSem IS NULL OR endSem <= $end) AND csFlag = 1
					ORDER BY cAbbrev ASC;");
			}
			else
			{
				$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev from Course WHERE beginSem <= $start AND (endSem IS NULL OR endSem <= $end) AND seFlag = 1
					ORDER BY cAbbrev ASC;");
			}
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a list of semesters in a given range
		* @param $start - first semester in range (inclusive)
		* @param $end - last semester in range (inclusive)
		* @return Array of semesters in the given range
		*/	
		public function getSemestersInRange($start, $end)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT * FROM Semester WHERE semesterId >= $start AND semesterId <= $end ORDER BY semesterId ASC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of courses which have outcome $oAbbrev
		* @param $oAbbrev - outcome abbreviation
		* @return Array of courses which have outcome $oAbbrev
		*/	
		public function getCoursesForOutcome($oAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cAbbrev FROM CourseOutcome WHERE oAbbrev = '$oAbbrev';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Gets the percentage of students who passed a given outcome for an offering given by 
		*  a course, semester, and section number 
		* @param $outcome - outcome abbreviation
		* @param $cAbbrev - course abbreviation or ALL
		* @param $sectionNo - section number
		* @param $semesterId - semester ID
		* @return Percentage of students who passed the outcome
		*/	
		public function calculatePercent($outcome, $course, $semester)
		{
			$stmt = $this->dbRead->prepare(
				"CALL calculatePercent('$outcome', '$course', 'AL', $semester, $semester);");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get a list of section numbers for offerings given by ($cAbbrev, $semesterId)
		* @param $cAbbrev - course abbreviation
		* @param $semesterId - semester ID
		* @return Array of section numbers for offerings given by ($cAbbrev, $semesterId)
		*/	
		public function getClassSectionNumbers($cAbbrev, $semesterId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT sectionNo FROM Offering WHERE cAbbrev = '$cAbbrev' AND semesterId = $semesterId;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
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
				"SELECT semester FROM Semester WHERE semesterId=$semesterId;");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['semester'];
		}
		
		/** 
		* Get course name for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Course name for course $cAbbrev
		*/	
		public function getCourseName($cAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cName from Course WHERE cAbbrev='$cAbbrev';");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['cName'];
		}
	}
?>