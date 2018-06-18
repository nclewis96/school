<?php

	/** 
	* Faculty Model - retrieves information from database
	*/
	class FacultyModel
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
		* Get offering information for offering $offeringId
		* @param $offeringId - offering ID
		* @return Offering information for offering $offeringId
		*/	
		public function getOfferingInformation($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT sectionNo, fName, cAbbrev, semesterId
				FROM Offering
				WHERE offeringId = $offeringId;");
			
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
		* Get course name for course $cAbbrev
		* @param $cAbbrev - course abbreviation
		* @return Course name for course $cAbbrev
		*/	
		public function getCourseName($courseAbbrev)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT cName FROM Course WHERE cAbbrev = '$courseAbbrev';");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['cName'];
		}
		
		/** 
		* Get a list of all outcomes for a course with offering $offeringId
		* @param $offeringId - offering ID
		* @return Array of outcomes for course course with offering $offeringId
		*/	
		public function getCourseOutcomes($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT OffOutcome.oAbbrev, oText
				FROM OffOutcome JOIN Outcome ON OffOutcome.oAbbrev = Outcome.oAbbrev
				WHERE offeringId = $offeringId ORDER BY OffOutcome.oAbbrev;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
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
				"SELECT sName, studentId
				FROM Student
				WHERE offeringId = $offeringId ORDER BY sName;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/* THESE FUNCTIONS ARE USED FOR THE ASSESSMENT PAGE ONLY */
		
		/** 
		* Get a list semesters in which user $userId is an instructor of an offering
		* @param $userId - user ID
		* @return Array of semesters in which user $userId is an instructor of an offering
		*/	
		public function getSemestersTaught($userId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT DISTINCT semester, Semester.semesterId 
				FROM Semester 
				JOIN Offering ON Offering.semesterId = Semester.semesterId 
				JOIN User ON Offering.userId = User.userId 
				WHERE User.userId = '$userId' ORDER BY semesterId DESC;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list courses taught by user $userId in semester $semester
		* @param $userId - user ID
		* @param $semester - semester name
		* @return Array of course information taught by user $userId in semester $semester
		*/	
		public function getCoursesForSemester($userId, $semester)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT Course.cAbbrev, cName, sectionNo, Offering.offeringId
				FROM Course
				JOIN Offering ON Offering.cAbbrev = Course.cAbbrev
				JOIN Semester ON Offering.semesterId = Semester.semesterId
				WHERE userId = '$userId' AND Semester.semester = '$semester';");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get a list of assessments for an offering given by ($cAbbrev, $sectionNo, $semester)
		* @param $cAbbrev - course abbreviation
		* @param $sectionNo - section number
		* @param $semester - semester name
		* @return Array of assessments for an offering given by ($cAbbrev, $sectionNo, $semester)
		*/	
		public function getAssessmentsForCourse($cAbbrev, $sectionNo, $semester)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT description, assessId
				FROM Assessment
				JOIN Offering ON Offering.offeringId = Assessment.offeringId
				JOIN Semester ON Semester.semesterId = Offering.semesterId
				WHERE cAbbrev = '$cAbbrev' AND sectionNo = '$sectionNo' AND Semester.semester = '$semester';");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get assessment information for assessment $assessmentId
		* @param $assessmentId - assessment ID
		* @return Array of assessment information for assessment $assessmentId
		*/	
		public function getAssessmentInformation($assessmentId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT description, maxPoints, offeringId
				FROM Assessment
				WHERE assessId = $assessmentId;");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result;
		}
		
		/** 
		* Get a list of outcomes associated with assessment $assessmentId
		* @param $assessmentId - assessment ID
		* @return Array of outcomes associated with assessment $assessmentId
		*/	
		public function getOutcomesForAssessment($assessmentId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT Outcome.oAbbrev, oText
				FROM AssessOutcome JOIN Outcome ON Outcome.oAbbrev = AssessOutcome.oAbbrev
				WHERE assessId = $assessmentId;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}

		/** 
		* Get a student's score for assessment $assessmentId
		* @param $assessmentId - assessment ID
		* @param $studentId -student ID
		* @return Student's score for assessment $assessmentId
		*/	
		public function getStudentScoreForAssessment($assessmentId, $studentId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT score FROM Score WHERE studentId = $studentId AND assessId = $assessmentId;");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['score'];
		}
		
		/* THESE FUNCTIONS ARE USED BY THE OFFERING PAGE ONLY */
		
		/** 
		* Gets the percentage of students who passed a given outcome for an offering given by 
		*  a course, semester, and section number 
		* @param $outcome - outcome abbreviation
		* @param $cAbbrev - course abbreviation or ALL
		* @param $sectionNo - section number
		* @param $semesterId - semester ID
		* @return Percentage of students who passed the outcome
		*/	
		public function calcPercent($outcome, $cAbbrev, $sectionNo, $semesterId)
		{
			$stmt = $this->dbRead->prepare(
				"CALL calculatePercent('$outcome', '$cAbbrev', '$sectionNo', $semesterId, $semesterId);");
				
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['score'];
		}
		
		/* THESE FUNCTIONS ARE USED BY THE FORMPROCESSOR PAGE ONLY */
		
		/** 
		* Add an assessment for offering $offeringId
		* @param $desc - assessment  description
		* @param $maxPoints - assessment's maximum point value
		* @param $offeringId - offering ID
		* @return Assessment ID for the added assessment
		*/	
		public function insertAssessment($desc, $maxPoints, $offeringId)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Assessment (description, maxPoints, offeringId) 
				VALUES ('$desc', $maxPoints, $offeringId);");
			
			$stmt->execute();
			
			$stmt = $this->dbRead->prepare(
				"SELECT assessId FROM Assessment 
				WHERE description = '$desc' 
				AND maxPoints = $maxPoints AND offeringId = $offeringId;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['assessId'];
		}
		
		/** 
		* Add a score for assessment $assessId
		* @param $assessId - assessment ID
		* @param $studentId - student ID
		* @param $score - the student's score
		*/	
		public function insertAssessmentScore($assessId, $studentId, $score)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Score VALUES ($assessId, $studentId, $score);");
			
			$stmt->execute();
		}
		
		/** 
		* Add an outcome for assessment $assessId
		* @param $assessId - assessment ID
		* @param $outcome - outcome abbreviation
		*/	
		public function insertAssessmentOutcome($assessId, $outcome)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO AssessOutcome (assessId, oAbbrev)
				Values ($assessId, '$outcome');");
			
			$stmt->execute();
		}
		
		/** 
		* Update assessment $assessId
		* @param $assessId - assessment ID
		* @param $desc - new assessment description
		* @param $maxPoints - new maximum point value for assessment
		*/	
		public function updateAssessment($assessId, $desc, $maxPoints)
		{
			$stmt = $this->dbWrite->prepare(
				"UPDATE Assessment 
				SET description = '$desc', maxPoints = $maxPoints 
				WHERE assessId = $assessId;");
				
			$stmt->execute();
		}
		
		/** 
		* Update an assessment score
		* @param $assessId - assessment ID
		* @param $studentId - student ID
		* @param $score - student's new score
		*/
		public function updateAssessmentScore($assessId, $studentId, $score)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Score VALUES ($assessId, $studentId, $score)
				ON DUPLICATE KEY UPDATE score = $score;");
			
			$stmt->execute();
		}
		
		/** 
		* Delete all outcomes for assessment $assessId
		* @param $assessId - assessment ID
		*/
		public function deleteAssessmentOutcomes($assessId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM AssessOutcome WHERE assessId = $assessId;");
			
			$stmt->execute();
		}
		
		/** 
		* Delete all scores for assessment $assessId
		* @param $assessId - assessment ID
		*/
		public function deleteAssessmentScores($assessId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Score WHERE assessId = $assessId;");
			
			$stmt->execute();
		}
		
		/** 
		* Delete assessment $assessId
		* @param $assessId - assessment ID
		*/
		public function deleteAssessment($assessId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Assessment WHERE assessId = $assessId;");
				
			$stmt->execute();
		}
		
		/** 
		* Insert a student into offering $offeringId
		* @param $name - student's name
		* @param $offeringId - offering ID
		* @return Student ID of the newly added student
		*/
		public function insertStudent($name, $offeringId)
		{
			$stmt = $this->dbWrite->prepare(
				"INSERT INTO Student (sName, offeringId) 
				VALUES ('$name', $offeringId);");
			
			$stmt->execute();
			
			$stmt = $this->dbRead->prepare(
				"SELECT studentId FROM Student 
				WHERE sName = '$name' AND offeringId = $offeringId;");
			
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			return $result['studentId'];
		}
		
		/** 
		* Get all assessment IDs for assessments associated with offering $offeringId
		* @param $offeringId - offering ID
		* @return Array of assessment IDs associated with offering $offeringId
		*/
		public function getAssessmentIds($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT assessId FROM Assessment WHERE offeringId = $offeringId;");
				
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Get all student names for students in offering $offeringId
		* @param $offeringId - offering ID
		* @return Array of student names for students in offering $offeringId
		*/
		public function getStudentNames($offeringId)
		{
			$stmt = $this->dbRead->prepare(
				"SELECT sName from Student WHERE offeringId = $offeringId;");
			
			$stmt->execute();
			$result = $stmt->fetchAll();
			return $result;
		}
		
		/** 
		* Delete student $studentId
		* @param $studentId - student ID of student to delete
		*/
		public function deleteStudent($studentId)
		{
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Score WHERE studentId = $studentId;");
			
			$stmt->execute();
			
			$stmt = $this->dbWrite->prepare(
				"DELETE FROM Student WHERE studentId = $studentId;");
			
			$stmt->execute();
		}
	}
?>