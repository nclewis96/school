<?php

include('../../application/reports/model/ReportsModel.php');

class ReportTest extends PHPUnit_Framework_TestCase
{
	private $DB;
	
	public function __construct()
	{
		$this->DB = new PDO('mysql:dbname=AbOut_Test;host=localhost', 'web_user', 'resu_bew');
		
		$this->model = new ReportsModel($this->DB, $this->DB);
	}

    public function test_getOutcomes()
    {
		$result = $this->model->getOutcomes();
		$this->assertCount(26, $result);
    }
	
    public function test_getSemesters()
    {
		$result = $this->model->getSemesters();
		$this->assertCount(8, $result);
    }
	
	public function test_getCourses()
    {
		$result = $this->model->getCourses();
		$this->assertCount(25, $result);
    }
	
	public function test_getCSCourses()
    {
		$result = $this->model->getCSCourses();
		$this->assertCount(20, $result);
    }
	
	public function test_getSECourses()
    {
		$result = $this->model->getSECourses();
		$this->assertCount(21, $result);
    }
	
	public function test_getCourseOutcomes()
    {
		$result = $this->model->getCourseOutcomes('CSCI 232');
		$this->assertCount(15, $result);
		
		$result = $this->model->getCourseOutcomes('FAKE 101');
		$this->assertEmpty($result);
    }
	
	public function test_getProgramOutcomes()
    {
		$result = $this->model->getProgramOutcomes('cac');
		$this->assertCount(11, $result);
		
		$result = $this->model->getProgramOutcomes('both');
		$this->assertCount(26, $result);
		
		$result = $this->model->getProgramOutcomes('eac');
		$this->assertCount(15, $result);
    }
	
	public function test_getProgramCoursesInRange()
    {
		// Unclear if function does what we want it to do
    }
	
	public function test_getSemestersInRange()
    {
		$result = $this->model->getSemestersInRange(1, 10);
		$this->assertCount(8, $result);
		
		$result = $this->model->getSemestersInRange(3, 8);
		$this->assertCount(4, $result);
		
		$result = $this->model->getSemestersInRange(2, 2);
		$this->assertCount(1, $result);
		
		$result = $this->model->getSemestersInRange(7, 2);
		$this->assertEmpty($result);
    }
	
	public function test_getCoursesForOutcome()
    {
		$result = $this->model->getCoursesForOutcome('CAC b');
		$this->assertCount(9, $result);
		
		$result = $this->model->getCoursesForOutcome('LOL z');
		$this->assertEmpty($result);		
    }
	
	public function test_calculatePercent()
    {
		$result = $this->model->calculatePercent('EAC e', 'ESOF 328', 2);
		$this->assertEquals(50, $result['score']);
    }
	
	public function test_getClassSectionNumbers()
    {
		$result = $this->model->getClassSectionNumbers('CSCI 332', 2);
		$this->assertCount(1, $result);
		
		$result = $this->model->getClassSectionNumbers('CSCI 332', 4);
		$this->assertEmpty($result);
    }
	
	public function test_getSemester()
    {
		$result = $this->model->getSemester(3);
		$this->assertEquals('Summer 2012', $result);
		
		$result = $this->model->getSemester(20);
		$this->assertEmpty($result);
    }
	
	public function test_getCourseName()
    {
		$result = $this->model->getCourseName('CSCI 361');
		$this->assertEquals('Computer Architecture', $result);
		
		$result = $this->model->getCourseName('FAKE 101');
		$this->assertEmpty($result);
    }
}
?>
