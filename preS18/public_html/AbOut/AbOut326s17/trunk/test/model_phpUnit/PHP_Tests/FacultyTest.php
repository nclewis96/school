<?php

include('../../application/faculty/model/FacultyModel.php');

class FacultyTest extends PHPUnit_Framework_TestCase
{
	private $DB;
	
	public function __construct()
	{
		$this->DB = new PDO('mysql:dbname=AbOut_Test;host=localhost', 'web_user', 'resu_bew');
		
		$this->model = new FacultyModel($this->DB, $this->DB);
	}

    public function test_getOfferingInformation()
    {
		$result = $this->model->getOfferingInformation(1);
		$this->assertEquals('ESOF 328', $result['cAbbrev']);
		$this->assertEquals(2, $result['semesterId']);
		$this->assertEquals('01', $result['sectionNo']);
		$this->assertEquals('Celia Schahczenski', $result['fName']);
		
		$result = $this->model->getOfferingInformation(500);
		$this->assertEmpty($result);
    }
	
	public function test_getSemester()
    {
		$result = $this->model->getSemester(9);
		$this->assertEquals('Fall 2013', $result);
		
		$result = $this->model->getSemester(15);
		$this->assertEmpty($result);
    }
	
	public function test_getCourseName()
    {
		$result = $this->model->getCourseName('CSCI 135');
		$this->assertEquals('Fundamentals of Computer Science I', $result);
		
		$result = $this->model->getCourseName('FAKE 101');
		$this->assertEmpty($result);
    }
	
	public function test_getCourseOutcomes()
    {
		$result = $this->model->getCourseOutcomes(3);
		$this->assertCount(10, $result);
		
		$result = $this->model->getCourseOutcomes(500);
		$this->assertEmpty($result);
    }
	
	public function test_getStudentsForOffering()
    {
		$result = $this->model->getStudentsForOffering(4);
		$this->assertCount(6, $result);
		
		$result = $this->model->getStudentsForOffering(500);
		$this->assertEmpty($result);
    }
	
	public function test_getSemestersTaught()
    {
		$result = $this->model->getSemestersTaught(4);
		$this->assertCount(4, $result);
		
		$result = $this->model->getSemestersTaught(100);
		$this->assertEmpty($result);
    }
	
	public function test_getCoursesForSemester()
    {
		$result = $this->model->getCoursesForSemester(1, 'Spring 2012');
		$this->assertCount(2, $result);
		
		$result = $this->model->getCoursesForSemester(30, 30);
		$this->assertEmpty($result);
    }
	
	public function test_getAssessmentsForCourse()
    {
		$result = $this->model->getAssessmentsForCourse('ESOF 328', '01', 'Spring 2012');
		$this->assertCount(14, $result);
		
		$result = $this->model->getCoursesForSemester('FAKE 101', '20', 'Winter 2112');
		$this->assertEmpty($result);
    }

	public function test_getAssessmentInformation()
    {
		$result = $this->model->getAssessmentInformation(73);
		$this->assertEquals('Final, question 3', $result['description']);
		$this->assertEquals(100, $result['maxPoints']);
		$this->assertEquals('1', $result['offeringId']);
		
		$result = $this->model->getAssessmentInformation(400);
		$this->assertEmpty($result);
    }
	
	public function test_getOutcomesForAssessment()
    {
		$result = $this->model->getOutcomesForAssessment(4);
		$this->assertCount(7, $result);
		
		$result = $this->model->getAssessmentInformation(400);
		$this->assertEmpty($result);
    }
	
	public function test_insertAssessment()
    {
		$this->model->insertAssessment('Test Assessment', 50, 1);
		
		$result = $this->model->getAssessmentInformation(369);
		$this->assertEquals('Test Assessment', $result['description']);
		$this->assertEquals(50, $result['maxPoints']);
		$this->assertEquals(1, $result['offeringId']);
    }
	
	public function test_insertAssessmentScore()
    {
		$this->model->insertAssessmentScore(369, 1, 45);
		
		$result = $this->model->getStudentScoreForAssessment(369, 1);
		$this->assertEquals(45, $result);
    }
	
	public function test_getStudentScoreForAssessment()
    {
		$result = $this->model->getStudentScoreForAssessment(70, 1);
		$this->assertEquals(69, $result);
		
		$result = $this->model->getStudentScoreForAssessment(500, 200);
		$this->assertEmpty($result);
    }
	
	public function test_insertAssessmentOutcome()
    {
		$result = $this->model->getOutcomesForAssessment(100);
		$this->assertCount(5, $result);
    }
	
	public function test_calcPercent()
    {
		$result = $this->model->calcPercent('EAC e', 'ESOF 328', '01', 2);
		$this->assertEquals(50, $result);
    }
	
	public function test_updateAssessment()
    {
		$this->model->updateAssessment(369, 'Test Assessment ver. 2', 100);
		
		$result = $this->model->getAssessmentInformation(369);
		$this->assertEquals('Test Assessment ver. 2', $result['description']);
		$this->assertEquals(100, $result['maxPoints']);
    }
	
	public function test_updateAssessmentScore()
    {
		$this->model->updateAssessmentScore(70, 123, 90);
		
		$result = $this->model->getStudentScoreForAssessment(70, 123);
		$this->assertEquals(90, $result);
    }
	
	public function test_deleteAssessmentOutcomes()
    {
		$this->model->deleteAssessmentOutcomes(22);
		
		$result = $this->model->getOutcomesForAssessment(22);
		$this->assertEmpty($result);
    }
	
	public function test_deleteAssessmentScores()
    {
		$this->model->deleteAssessmentScores(369);
		
		$result = $this->model->getStudentScoreForAssessment(369, 1);
		$this->assertEmpty($result);
    }
	
	public function test_deleteAssessment()
    {
		$this->model->deleteAssessmentOutcomes(4);
		$this->model->deleteAssessment(4);
		
		$result = $this->model->getAssessmentInformation(4);
		$this->assertEmpty($result);
    }
	
	public function test_insertStudent()
    {
		$this->model->insertStudent('Good Student', 100);
		
		$result = $this->model->getStudentsForOffering(100);
		$this->assertCount(9, $result);
    }
	
	public function test_getAssessmentIds()
    {
		$result = $this->model->getAssessmentIds(2);
		$this->assertCount(18, $result);
		
		$result = $this->model->getAssessmentIds(400);
		$this->assertEmpty($result);
    }
	
	public function test_getStudentNames()
    {
		$result = $this->model->getStudentNames(106);
		$this->assertCount(12, $result);
		
		$result = $this->model->getStudentNames(200);
		$this->assertEmpty($result);
    }
	
	public function test_deleteStudent()
    {
		$this->model->deleteStudent(859);
		
		$result = $this->model->getStudentNames(106);
		$this->assertCount(11, $result);
    }
}
?>
