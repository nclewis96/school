<?php

include('../../application/admin/model/AdminModel.php');

class AdminTest extends PHPUnit_Framework_TestCase
{
	private $DB;
	
	public function __construct()
	{
		$this->DB = new PDO('mysql:dbname=AbOut_Test;host=localhost', 'web_user', 'resu_bew');

		$this->model = new AdminModel($this->DB, $this->DB);
	}

    public function test_getCourses()
    {
		$result = $this->model->getCourses();
		$this->assertCount(25, $result);
    }
	
	public function test_getOfferings()
    {
		$result = $this->model->getOfferings('CSCI 135');
		$this->assertCount(2, $result);
		
		$result = $this->model->getOfferings('FAKE 101');
		$this->assertEmpty($result);
    }
	
	public function test_getOutcomes()
    {
		$result = $this->model->getOutcomes();
		$this->assertCount(26, $result);
    }
	
	public function test_getUsers()
    {
		$result = $this->model->getUsers();
		$this->assertCount(9, $result);
    }
	
	public function test_getSemesters()
    {
		$result = $this->model->getSemesters();
		$this->assertCount(8, $result);
    }
	
	public function test_getCourse()
    {
		$result = $this->model->getCourse('CSCI 438');
		$this->assertEquals('Theory of Computation', $result['cName']);
		$this->assertEquals(1, $result['csFlag']);
		$this->assertEquals(0, $result['seFlag']);
		$this->assertEquals(1, $result['beginSem']);
		$this->assertNull($result['endSem']);
		
		$result = $this->model->getCourse('FAKE 101');
		$this->assertEmpty($result);
    }
	
	public function test_getSemester()
    {
		$result = $this->model->getSemester(1);
		$this->assertEquals('Fall 2011', $result);
		
		$result = $this->model->getSemester(20);
		$this->assertEmpty($result);
    }
	
	public function test_getSemestersGreaterThan()
    {
		$result = $this->model->getSemestersGreaterThan(1);
		$this->assertCount(8, $result);
		
		$result = $this->model->getSemestersGreaterThan(7);
		$this->assertCount(4, $result);
		
		$result = $this->model->getSemestersGreaterThan(10);
		$this->assertCount(1, $result);
		
		$result = $this->model->getSemestersGreaterThan(11);
		$this->assertEmpty($result);
    }
	
	public function test_getCSOutcomes()
    {
		$result = $this->model->getCSOutcomes();
		$this->assertCount(11, $result);
    }
	
	public function test_getSEOutcomes()
    {
		$result = $this->model->getSEOutcomes();
		$this->assertCount(15, $result);
    }
	
	public function test_getCourseOutcomes()
    {
		$result = $this->model->getCourseOutcomes('CSCI 246');
		$this->assertCount(3, $result);
		
		$result = $this->model->getCourseOutcomes('FAKE 101');
		$this->assertEmpty($result);
    }
	
	public function test_getOffering()
    {
		$result = $this->model->getOffering(1);
		$this->assertEquals('ESOF 328', $result['cAbbrev']);
		$this->assertEquals(2, $result['semesterId']);
		$this->assertEquals('01', $result['sectionNo']);
		$this->assertEquals('Celia Schahczenski', $result['fName']);
		
		$result = $this->model->getOffering(500);
		$this->assertEmpty($result);
    }
	
	public function test_getStudentsForOffering()
    {
		$result = $this->model->getStudentsForOffering(4);
		$this->assertCount(6, $result);
		
		$result = $this->model->getStudentsForOffering(500);
		$this->assertEmpty($result);
    }
	
	public function test_getOutcome()
    {
		$result = $this->model->getOutcome('CAC a');
		$this->assertEquals('An ability to apply knowledge of computing and mathematics appropriate to the discipline', $result['oText']);
		$this->assertEquals('CS', $result['pAbbrev']);
		$this->assertEquals(1, $result['beginSem']);
		$this->assertNull($result['endSem']);
		
		$result = $this->model->getOutcome('LOL z');
		$this->assertEmpty($result);
    }
	
	public function test_getCurrentSemester()
    {
		$result = $this->model->getCurrentSemester();
		$this->assertEquals('Spring 2014', $result);
    }
	
	public function test_getUser()
    {
		$result = $this->model->getUser(2);
		$this->assertEquals('Jon Wareham/Tami', $result['uName']);
		$this->assertEquals('jcwareham', $result['usernameCAS']);
		$this->assertEquals(0, $result['activeFlag']);
		
		$result = $this->model->getUser(50);
		$this->assertEmpty($result);
    }
	
	public function test_setDefaultSemester()
    {
		$this->model->setDefaultSemester(3);
		
		$stmt = $this->DB->prepare("SELECT semesterId FROM DefaultSemester;");
		$stmt->execute();
		$result = $stmt->fetch(PDO::FETCH_ASSOC);
		$this->assertEquals(3, $result['semesterId']);
		
		$this->model->setDefaultSemester(10);
    }
	
	public function test_addSemester()
    {
		$result = $this->model->addSemester('Spring 2112');
		
		$result = $this->model->getSemester($result);
		$this->assertEquals('Spring 2112', $result);
		
		$stmt = $this->DB->prepare("DELETE FROM Semester WHERE semester = 'Spring 2112';");
		$stmt->execute();
    }
	
	public function test_addOutcome() 
    {
		$this->model->addOutcome('CAC z', 'test outcome', 'CS', 1, 10);
		$result = $this->model->getOutcome('CAC z');
		$this->assertEquals('test outcome', $result['oText']);
		$this->assertEquals('CS', $result['pAbbrev']);
		$this->assertEquals(1, $result['beginSem']);
		$this->assertEquals(10, $result['endSem']);
    }
	
	public function test_deleteOutcome()  
    {
		$this->model->deleteOutcome('CAC z');
		$result = $this->model->getOutcome('CAC z');
		$this->assertEmpty($result);
    }
	
	public function test_updateOutcome()
    {
		$this->model->updateOutcome('CAC a', 'modified description', 'CS', 3, 10);
		$result = $this->model->getOutcome('CAC a');
		$this->assertEquals('modified description', $result['oText']);
		$this->assertEquals('CS', $result['pAbbrev']);
		$this->assertEquals(3, $result['beginSem']);
		$this->assertEquals(10, $result['endSem']);
    }
	
	public function test_addUser()
    {
		$result = $this->model->addUser('test', 'Test User', 0);
		$result = $this->model->getUser($result);
		$this->assertEquals('Test User', $result['uName']);
		$this->assertEquals('test', $result['usernameCAS']);
		$this->assertEquals(0, $result['activeFlag']);
    }
	
	public function test_deleteUser()
    {
		$this->model->deleteUser(12);
		$result = $this->model->getUser(12);
		$this->assertEmpty($result);
    }
	
	public function test_updateUser()
    {
		$this->model->updateUser(1, 'asdf', 'Updated User', 0);
		$result = $this->model->getUser(1);
		$this->assertEquals('Updated User', $result['uName']);
		$this->assertEquals('asdf', $result['usernameCAS']);
		$this->assertEquals(0, $result['activeFlag']);
    }
	
	public function test_addCourse()
    {
		$outcomes = array("CAC a", "EAC a");
		$this->model->addCourse('TEST 101', 'Test Course', 0, 1, 3, 10, $outcomes);
		$result = $this->model->getCourse('TEST 101');
		$this->assertEquals('Test Course', $result['cName']);
		$this->assertEquals(0, $result['csFlag']);
		$this->assertEquals(1, $result['seFlag']);
		$this->assertEquals(3, $result['beginSem']);
		$this->assertEquals(10, $result['endSem']);
		
		$result = $this->model->getCourseOutcomes('TEST 101');
		$this->assertCount(2, $result);
    }
	
	public function test_deleteCourse()
    { 
		$this->model->deleteCourse('TEST 101');
		$result = $this->model->getCourse('TEST 101');
		$this->assertEmpty($result);
    }
	
	public function test_updateCourse()
    {
		$outcomes = array("CAC a", "EAC a", "EAC b");
		$this->model->updateCourse('CSCI 470', 'Not Web Science', 1, 1, 10, $outcomes);
		$result = $this->model->getCourse('CSCI 470');
		$this->assertEquals('Not Web Science', $result['cName']);
		$this->assertEquals(1, $result['csFlag']);
		$this->assertEquals(1, $result['seFlag']);
		$this->assertEquals(10, $result['endSem']);
		
		$result = $this->model->getCourseOutcomes('CSCI 470');
		$this->assertCount(3, $result);
    }
	
	public function test_addOffering()
    {
		$result = $this->model->addOffering('ESOF 427', 10, '01', 2);
		$result = $this->model->getOffering(110);
		$this->assertEquals('ESOF 427', $result['cAbbrev']);
		$this->assertEquals(10, $result['semesterId']);
		$this->assertEquals('01', $result['sectionNo']);
		$this->assertEquals('Jon Wareham/Tami', $result['fName']);
    }
	
	public function test_deleteOffering()
    {
		$this->model->deleteOffering(110);
		$result = $this->model->getOffering(110);
		$this->assertEmpty($result);
    }
	
	public function test_updateOffering()
    {
		$this->model->updateOffering(100, '02', 2);
		$result = $this->model->getOffering(100);
		$this->assertEquals('02', $result['sectionNo']);
		$this->assertEquals('Jon Wareham/Tami', $result['fName']);
    }
	
	public function test_addStudentsToOffering()
    {
		$this->model->addStudentsToOffering(108, array('Student 1', 'Student 2'));
		$result = $this->model->getStudentsForOffering(108);
		$this->assertCount(11, $result);
    }
	
	public function test_removeAllStudentsFromOffering()
    {
		$this->model->removeAllStudentsFromOffering(9);
		$result = $this->model->getStudentsForOffering(9);
		$this->assertEmpty($result);
    }
	
	public function test_removeStudentFromOffering()
    {
		$this->model->removeStudentFromOffering(890, 108);
		$result = $this->model->getStudentsForOffering(108);
		$this->assertCount(10, $result);
    }
	
	public function test_getCoursePrefixes()
    {
		$result = $this->model->getCoursePrefixes();
		$this->assertCount(3, $result);
    }
	
	public function test_getOutcomePrefixes()
    {
		$result = $this->model->getOutcomePrefixes();
		$this->assertCount(2, $result);
    }
	
	public function test_getCourseOffering()
    {
		$result = $this->model->getCourseOffering('CSCI 361', 7, '01');
		$this->assertEquals(1, $result);
		
		$result = $this->model->getCourseOffering('FAKE 101', 'Spring 2018', '05');
		$this->assertEquals(0, $result);
    }
}
?>
