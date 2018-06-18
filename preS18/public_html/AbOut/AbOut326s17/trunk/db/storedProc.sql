/* 

storedProc.sql

These stored procedures live in the AbOut database. 
If changes are made to this file, place those changes into the db by 
going into mysql using the AbOut db and entering: 
	mysql> source storedProc.sql

To call one of the procedures: 
	mysql> CALL procedureName(parameters);

To see a procedure's definition: 
	mysql> SHOW CREATE PROCEDURE procedureName;
(However it is easier just to look at this file.)

To call this from php: 
       $stmt = $DB_Read->prepare("call procedureName(parameters);");

The results will be returned as usual.

*/


DELIMITER //

/**  semesters ****************************************************/

DROP PROCEDURE IF EXISTS semesters //

/**
 * semesters - Take one or two semester ids and return the 
 * 							semester names
 * Parameters:
 * 	semesterId1 
 *	semesterId2
 * Returns: 
 * 	semName1 - name of first semester or NULL if illegal semester id
 *	semName2 - name of second semester or NULL
 *
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 */
CREATE PROCEDURE semesters(
			IN in_sem1 INTEGER, 
			IN in_sem2 INTEGER
				    )
BEGIN
 
	DECLARE semName1 CHAR(12);
	DECLARE semName2 CHAR(12);

	SELECT semester
	FROM Semester
	WHERE semesterID=in_sem1 
	INTO semName1;

	IF semName1 IS NULL THEN
		SELECT "NULL" INTO semName1;
	END IF; 


	SELECT semester
	FROM Semester
	WHERE semesterID=in_sem2 
	INTO semName2; 

	IF semName2 IS NULL THEN
		SELECT "NULL" INTO semName2;
	END IF; 

	/* Create the query */
	set @query = CONCAT (
		"SELECT '", semName1, "' AS semName1, '", semName2, "' AS semName2;"
				);

	/* Use to debug  
	select @query; */

	/* Execute the query */  
	PREPARE stmt FROM @query;
	EXECUTE stmt; 

END //



/**  outcomes ********************************************************/

DROP PROCEDURE IF EXISTS outcomes //

/**
 * outcomes - Returns outcome abbreviations and text for those outcomes 
 *            within a program and in a semseter range.
 * Parameters:
 * 	program abbreviation
 *	semesterId begin
 * 	semesterId end
 * Returns a set of: 
 * 	oAbbrev - abbreviation for outcome
 *	oText - text of outcome
 * 
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 */
CREATE PROCEDURE outcomes(
			IN in_pAbbrev CHAR(3),
 			IN in_sem1 INTEGER,
			IN in_sem2 INTEGER
				    )
BEGIN

	/* Null second semester indicates single semester */
	IF in_sem2 IS NULL THEN 
		SELECT in_sem1 INTO in_sem2; 
	END IF; 


	/* Create string for WHERE to handle the program. */
	IF in_pAbbrev='CAC' OR in_pAbbrev='EAC' THEN 
		set @pgmLimit = CONCAT("pAbbrev='", in_pAbbrev, "' AND ");
	ELSE 
		set @pgmLimit = "";
	END IF;

	/* Create the query */
	set @query = CONCAT (
		"SELECT oAbbrev, oText "
		"FROM Outcome ",
		"WHERE ", @pgmLimit, 
		    in_sem2, " >= beginSem AND ", 
		    "((endSem IS NULL) OR (", in_sem1, " <= endSem));" 
				);

	/* Use to debug 
	select @query; */

	/* Execute the query */
	PREPARE stmt FROM @query;
	EXECUTE stmt;

END //


/** partialOutcomes  *******************************************************/

DROP PROCEDURE IF EXISTS partialOutcomes //

/**
 * partialOutcomes - Returns outcome abbreviations, beginSem name and 
 *                        endSem name for those outcomes which are 
 *                        only active for a portion of the semester 
 * 			     range.
 * Parameters:
 * 	program abbreviation
 *	semesterId begin
 * 	semesterId end
 * Returns a set of: 
 * 	oAbbrev - abbreviation for outcome
 * 	semName1 - name of semester when the outcome became active
 *	semName2 - name of the last semester when the outcome was active, 
 *                                          or null
 * 
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 */
CREATE PROCEDURE partialOutcomes(
			IN in_pAbbrev CHAR(3),
 			IN in_sem1 INTEGER,
			IN in_sem2 INTEGER
				    )
BEGIN

	/* Null second semester indicates single semester */
	IF in_sem2 IS NULL THEN 
		SELECT in_sem1 INTO in_sem2; 
	END IF; 


	/* Create string for WHERE to handle the program. */
	IF in_pAbbrev='CAC' OR in_pAbbrev='EAC' THEN 
		set @pgmLimit = CONCAT("pAbbrev='", in_pAbbrev, "' AND ");
	ELSE 
		set @pgmLimit = " ";
	END IF;

	/* Create the query */
	set @query = CONCAT (
		"SELECT oAbbrev, Begin.semester AS oBegSemName, ", 
			"End.semester AS oEndSemName ", 
		"FROM (", 
			"SELECT oAbbrev, beginSem, endSem ",
			"FROM Outcome ",
			"WHERE ", @pgmLimit,
				/* Restirct to outcomes in range */ 
				in_sem2, " >= beginSem AND ", 
				"(endSem IS NULL OR ", in_sem1, " <= endSem) AND ", 
				/* Further only keep outcomes not active 
			  	 throughout the range */ 
				"(", in_sem1, "<beginSem OR "
				"(NOT endSem IS NULL AND ", in_sem2, " > endSem))", 
			") AS Temp ",
			"JOIN Semester AS Begin ON Temp.beginSem=Begin.semesterId ", 
			"LEFT OUTER JOIN Semester AS End ON Temp.endSem=End.semesterId;"
				);


	/* Use to debug 
	select @query; */

	/* Execute the query */
	PREPARE stmt FROM @query;
	EXECUTE stmt;


END //

/**  courses  ********************************************************/

DROP PROCEDURE IF EXISTS courses //

/**
 * courses - Returns course abbreviations for those courses 
 *            within a program and in a semseter range.
 * Parameters:
 * 	program abbreviation
 *	semesterId begin
 * 	semesterId end
 * Returns a set of: 
 * 	cAbbrev - abbreviation for course
 * 
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 */
CREATE PROCEDURE courses(
			IN in_pAbbrev CHAR(3),
 			IN in_sem1 INTEGER,
			IN in_sem2 INTEGER
				    )
BEGIN

	/* Null second semester indicates single semester */
	IF in_sem2 IS NULL THEN 
		SELECT in_sem1 INTO in_sem2; 
	END IF; 


	/* Create string for WHERE to handle the program. */
	IF in_pAbbrev='CAC' THEN 
		set @pgmLimit = CONCAT("csFlag=1 AND ");
	ELSE IF in_pAbbrev='EAC' THEN 
		set @pgmLimit = CONCAT("seFlag=1 AND ");
	ELSE
		set @pgmLimit = " ";
	END IF; 
	END IF;

	/* Create the query */
	set @query = CONCAT (
		"SELECT cAbbrev ", 
		"FROM Course ",
		"WHERE ", @pgmLimit,
			in_sem2, " >= beginSem AND ", 
			"(endSem IS NULL OR ", in_sem1, " <= endSem);"
				);

	/* Use to debug 
	select @query; */

	/* Execute the query */
	PREPARE stmt FROM @query;
	EXECUTE stmt; 

END //


/**  partialCourses ***************************************************/

DROP PROCEDURE IF EXISTS partialCourses //

/**
 * partialCourses - Returns course abbreviations, beginSem name and 
 *                        endSem name for those courses which are 
 *                        only active for a portion of the semester 
 * 			     range.
 * Parameters:
 * 	program abbreviation
 *	semesterId begin
 * 	semesterId end
 * Returns a set of: 
 * 	cAbbrev - abbreviation for course
 * 
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 */
CREATE PROCEDURE partialCourses(
			IN in_pAbbrev CHAR(3),
 			IN in_sem1 INTEGER,
			IN in_sem2 INTEGER
				    )
BEGIN

	/* Null second semester indicates single semester */
	IF in_sem2 IS NULL THEN 
		SELECT in_sem1 INTO in_sem2; 
	END IF; 


	/* Create string for WHERE to handle the program. */
	IF in_pAbbrev='CAC' THEN 
		set @pgmLimit = CONCAT("csFlag=1 AND ");
	ELSE IF in_pAbbrev='EAC' THEN 
		set @pgmLimit = CONCAT("seFlag=1 AND ");
	ELSE
		set @pgmLimit = " ";
	END IF; 
	END IF;

	/* Create string for WHERE to handle the program. */
	IF in_pAbbrev='CAC' THEN 
		set @pgmLimit = CONCAT("csFlag=1 AND ");
	ELSE IF in_pAbbrev='EAC' THEN 
		set @pgmLimit = CONCAT("seFlag=1 AND ");
	ELSE
		set @pgmLimit = " ";
	END IF; 
	END IF;

	/* Create the query */
	set @query = CONCAT (
		"SELECT cAbbrev, Begin.semester AS cBegSemName, ", 
			"End.semester AS cEndSemName ", 
		"FROM ( ", 
			"SELECT cAbbrev, beginSem, endSem ", 
			"FROM Course ",
		"WHERE ", @pgmLimit,
			/* Restirct to outcomes in range */ 
			in_sem2, " >= beginSem AND ", 
			"(endSem IS NULL OR ", in_sem1, " <= endSem) AND ",
			/* Further only keep courses not active 
			throughout the range */ 
			"(", in_sem1, " < beginSem OR ",
			"(NOT endSem IS NULL AND ", in_sem2, " > endSem)) ", 
			") AS Temp ", 
			"JOIN Semester AS Begin ON Temp.beginSem=Begin.semesterId ", 
			"LEFT OUTER JOIN Semester AS End ON Temp.endSem=End.semesterId;" 
				);


	/* Use to debug 
	select @query; */

	/* Execute the query */
	PREPARE stmt FROM @query;
	EXECUTE stmt; 

END //




/** calculatePercent *********************************************/

DROP PROCEDURE IF EXISTS calculatePercent //

/**
 * calculatePercent - Given an outcome, course, section number and semester range, 
 *                   return the percentage of students who took 
 *			the offerings in the course in the range and passed the 
 *                   outcome.
 * Parameters:
 *	oAbbrev - outcome
 * 	cAbbrev - course or ALL
 * 	sectionNo - section number or 'AL' for all sections
 * 	beginSemId - beginning semester in range
 * 	endSemId - end semester or NULL
 * Returns: 
 * 	percent - percentage of students who passed this outcome
 *     noStud - number of students/offerings assessed, that is, 
 *                  a student in 3 offerings is counted 3 times
 *
 * For debugging, modify the bottom of this code to see @query
 * 	@query - the query as a string
 *
 * Example calls from php: 
 *     $stmt = $DB_Read->prepare("CALL calculatePercent('CAC a', 'CSCI135', 'AL', 6, 8);"); 
 *     $stmt = $DB_Read->prepare("CALL calculatePercent('CAC a', 'ALL', 'AL', 1, NULL);"); 
 *     $stmt = $DB_Read->prepare("CALL calculatePercent(".
 *							"'".$outcomes[$j]."', ".
 *							"'".$courses[$i]."', ". 
 *							"'AL', ".
 *							"$begSem, ".
 *							"$endSem ".
 *								 ");"
 *				    );
 *
 * Description of the query: for the course given, grab all 
 * offerings with the section number within the semester range. 
 * Take the assessments on those offerings which assess the 
 * given outcome, group by the students, sum the scores they 
 * got over the possible points and if over 70% count them.
 *
 */

CREATE PROCEDURE calculatePercent(
			IN in_oAbbrev CHAR(6),
			IN in_cAbbrev CHAR(10),
			IN in_sectionNo CHAR(2),
			IN in_sem1 INTEGER, 
			IN in_sem2 INTEGER 
 				    )
BEGIN

	SET @PASSING_GOAL = 70;

	/* Null second semester indicates single semester */
	IF in_sem2 IS NULL THEN 
		SELECT in_sem1 INTO in_sem2; 
	END IF; 

	/* Create string for WHERE to handle the course. */
	IF in_cAbbrev='ALL' THEN 
		set @courseLimit = "";
	ELSE 
		set @courseLimit = CONCAT("cAbbrev='", in_cAbbrev, "' AND ");
	END IF;

	/* Create string for WHERE to handle the section number. */
	IF in_sectionNo='AL' THEN 
		set @sectionLimit = "";
	ELSE 
		set @sectionLimit = CONCAT("sectionNo='", in_sectionNo, "' AND ");
	END IF;

	/* Create the query */
	set @query = CONCAT (
	"SELECT (SUM(pass)/COUNT(*))*100 AS score, COUNT(*) as noStud, SUM(pass) as noStudPass ",
	"FROM (",
		"SELECT (SUM(score)/SUM(maxPoints))*100>=", @PASSING_GOAL, " AS pass ",
		"FROM Score JOIN Assessment ", 
			"ON Score.assessId=Assessment.assessId ",
		"WHERE Assessment.assessId IN ",
			"(SELECT Assessment.assessId ", 
 	 		"FROM Assessment JOIN AssessOutcome ",
	 			"ON Assessment.assessId=AssessOutcome.assessId ",
			   "WHERE AssessOutcome.oAbbrev='", in_oAbbrev, "' ", 
			     "AND Assessment.offeringId IN ", 
					"(SELECT offeringId ", 
					"FROM Offering ", 
					"WHERE ", @courseLimit,
						@sectionLimit ,  
						"semesterId BETWEEN ", in_sem1, " AND ", in_sem2, 
					") ",
			") ",
		"GROUP BY studentId ", 
		") Temp ",
		";"
			      ); 

	/*Use to debug 
	select @query;*/

	/* Execute the query  */
	PREPARE stmt FROM @query;
	EXECUTE stmt; 


END //


DELIMITER ;

